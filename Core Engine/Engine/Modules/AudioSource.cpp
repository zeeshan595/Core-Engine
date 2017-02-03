void AudioSource::Play()
{
    alSourcePlay(source);
}

void AudioSource::Stop()
{
    alSourceStop(source);
}

void AudioSource::Pause()
{
    alSourcePause(source);
}

void  AudioSource::SetLooping(bool loop)
{
    if (loop)
        alSourcei(source, AL_LOOPING, AL_TRUE);
    else
        alSourcei(source, AL_LOOPING, AL_FALSE);
}

void AudioSource::SetPitch(float pitch)
{
    alSourcef(source, AL_PITCH, pitch);
}

void AudioSource::SetGain(float gain)
{
    alSourcef(source, AL_GAIN, gain);
}

void AudioSource::Is3DSound(bool is_3D)
{
    sound3D = is_3D;
    if (sound3D)
        alSourcef(source, AL_ROLLOFF_FACTOR, roll_off);
    else
        alSourcef(source, AL_ROLLOFF_FACTOR, 0.0f);
}

void AudioSource::SetRollOffFactor(float roll)
{
    alSourcef(source, AL_ROLLOFF_FACTOR, roll);
    roll_off = roll;
}

void AudioSource::SetReferenceDistance(float distance)
{
    alSourcef(source, AL_REFERENCE_DISTANCE, distance);
}

AudioSource::AudioSource()
{
    play_on_start = true;
    sound3D = true;
    roll_off = 1.0f;
}

AudioSource::~AudioSource()
{
    alDeleteBuffers(1, &buffer);
    alDeleteSources(1, &source);
}

void AudioSource::Start()
{
    if (play_on_start)
        alSourcePlay(source);
}

void AudioSource::Update()
{
    if (!sound3D)
    {
        glm::vec3 pos = Audio::GetListenerPosition();
        glm::vec3 vel = Audio::GetListenerVelocity();
        ALfloat source_position[] = { pos.x, pos.y, pos.z };
        ALfloat source_velocity[] = { vel.x, vel.y, vel.z };
        alSourcefv(source, AL_POSITION, source_position);
        alSourcefv(source, AL_VELOCITY, source_velocity);
    }
    else if (attached_to != nullptr)
    {
        ALfloat source_position[] = {
             attached_to->transform.position.x,
             attached_to->transform.position.y,
             attached_to->transform.position.z 
        };
        ALfloat source_velocity[] = { 0.0, 0.0, 0.0 };
        alSourcefv(source, AL_POSITION, source_position);
        alSourcefv(source, AL_VELOCITY, source_velocity);
    }
}

void AudioSource::LoadAudioFile(std::string filename)
{
    FILE* fp = NULL;
    char type[4];
    DWORD size, chunk_size;
    short format_type, channels;
    DWORD sample_rate, average_bytes_per_second;
    short bytes_per_sample, bits_per_sample;
    DWORD data_size;

    fp = fopen((SOUND_PATH + "Sound.wav").c_str(), "rb");
    //Check file is in proper format
    fread(type, sizeof(char), 4, fp);
    if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
    {
        std::cout << "NO RIFF" << std::endl;
        return;
    }

    fread(&size, sizeof(DWORD), 1, fp);
    fread(type, sizeof(char), 4, fp);
    if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
    {
        std::cout << "NO WAVE: " << std::endl;
        return;
    }

    fread(type, sizeof(char), 4, fp);
    if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
    {
        std::cout << "not fmt " << std::endl;
        return;
    }

    fread(&chunk_size, sizeof(DWORD), 1, fp);
    fread(&format_type, sizeof(short), 1, fp);
    fread(&channels, sizeof(short), 1, fp);
    fread(&sample_rate, sizeof(DWORD), 1, fp);
    fread(&average_bytes_per_second, sizeof(DWORD), 1, fp);
    fread(&bytes_per_sample, sizeof(short), 1, fp);
    fread(&bits_per_sample, sizeof(short), 1, fp);
    
    fread(type,sizeof(char), 4, fp);
    if (type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
    {
        std::cout << "Missing data" << std::endl;
        return;
    }
    fread(&data_size, sizeof(DWORD), 1, fp);
    unsigned char* data = new unsigned char[data_size];
    fread(data, sizeof(BYTE), data_size, fp);
    GenerateOpenALAudio(data, data_size, sample_rate, channels, bits_per_sample);
}

void AudioSource::GenerateOpenALAudio(unsigned char* data, DWORD data_size, DWORD sample_rate, short channels, short bits_per_sample)
{
    if (source != 0)
    {
        alDeleteBuffers(1, &buffer);
        alDeleteSources(1, &source);
    }

    ALuint frequency = sample_rate;
    ALenum format = 0;

    alGenBuffers(1, &buffer);
    alGenSources(1, &source);
    if (bits_per_sample == 8)
    {
        if (channels == 1)
            format = AL_FORMAT_MONO8;
        else if (channels == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if (bits_per_sample == 16)
    {
        if (channels == 1)
            format = AL_FORMAT_MONO16;
        else if (channels == 2)
            format = AL_FORMAT_STEREO16;
    }
    alBufferData(buffer, format, data, data_size, frequency);
    
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    alSourcef(source, AL_ROLLOFF_FACTOR, roll_off);
    alSourcef(source, AL_REFERENCE_DISTANCE, 10.0f);

    ALfloat source_position[] = { 0.0, 0.0, 0.0 };
    ALfloat source_velocity[] = { 0.0, 0.0, 0.0 };
    alSourcefv(source, AL_POSITION, source_position);
    alSourcefv(source, AL_VELOCITY, source_velocity);
    std::cout << "SUCCESS [Audio Loaded]" << std::endl;
}