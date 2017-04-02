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
    else if (entity != nullptr)
    {
        glm::vec3 pos = entity->transform.GetPosition();
        ALfloat source_position[] = { pos.x, pos.y, pos.z };
        ALfloat source_velocity[] = { 0.0, 0.0, 0.0 };
        alSourcefv(source, AL_POSITION, source_position);
        alSourcefv(source, AL_VELOCITY, source_velocity);
    }
}

AudioClip* AudioSource::GetClip()
{
    return audio_clip;
}

//unsigned char* data, DWORD data_size, DWORD sample_rate, short channels, short bits_per_sample
void AudioSource::SetClip(AudioClip* clip)
{
    audio_clip = clip;
    ALuint frequency = clip->GetSampleRate();
    ALenum format = 0;

    alGenBuffers(1, &buffer);
    alGenSources(1, &source);
    if (clip->GetBitsPerSample() == 8)
    {
        if (clip->GetChannels() == 1)
            format = AL_FORMAT_MONO8;
        else if (clip->GetChannels() == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if (clip->GetBitsPerSample() == 16)
    {
        if (clip->GetChannels() == 1)
            format = AL_FORMAT_MONO16;
        else if (clip->GetChannels() == 2)
            format = AL_FORMAT_STEREO16;
    }
    alBufferData(buffer, format, clip->GetData(), clip->GetDataSize(), frequency);

    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    alSourcef(source, AL_ROLLOFF_FACTOR, roll_off);
    alSourcef(source, AL_REFERENCE_DISTANCE, 1.0f);

    ALfloat source_position[] = { 0.0, 0.0, 0.0 };
    ALfloat source_velocity[] = { 0.0, 0.0, 0.0 };
    alSourcefv(source, AL_POSITION, source_position);
    alSourcefv(source, AL_VELOCITY, source_velocity);
    std::cout << "SUCCESS [Audio Loaded]" << std::endl;
}

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