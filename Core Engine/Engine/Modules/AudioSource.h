#ifndef _AUDIO_SOURCE
#define _ME_AUDIO_SOURCESH

class AudioSource : public Module
{
public:
    AudioSource()
    {
        FILE* fp = NULL;
        fp = fopen((SOUND_PATH + "Sound.wav").c_str(), "rb");
        char type[4];
        DWORD size, chunk_size;
        short format_type, channels;
        DWORD sample_rate, average_bytes_per_second;
        short bytes_per_sample, bits_per_sample;
        DWORD data_size;

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
        unsigned char* buf = new unsigned char[data_size];
        fread(buf, sizeof(BYTE), data_size, fp);

        ALCdevice* device;
        ALCcontext* context;
        device = alcOpenDevice(NULL);
        if(!device)
        {
            std::cout << "no sound device" << std::endl;
            return;
        }
        context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);
        if (!context)
        {
            std::cout << "no sound context" << std::endl;
            return;
        }
        ALuint source;
        ALuint buffer;
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
        alBufferData(buffer, format, buf, data_size, frequency);
        ALfloat source_position[]       = { 0.0, 0.0, 0.0 };
        ALfloat source_velocity[]       = { 0.0, 0.0, 0.0 };
        ALfloat listener_position[]     = { 0.0, 0.0, 0.0 };
        ALfloat listener_velocity[]     = { 0.0, 0.0, 0.0 };
        ALfloat listener_orientation[]  = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

        //Setup listener
        alListenerfv(AL_POSITION, listener_position);
        alListenerfv(AL_VELOCITY, listener_velocity);
        alListenerfv(AL_ORIENTATION, listener_orientation);

        //Setup Source
        alSourcei(source, AL_BUFFER, buffer);
        alSourcef(source, AL_PITCH, 1.0f);
        alSourcef(source, AL_GAIN, 1.0f);
        alSourcefv(source, AL_POSITION, source_position);
        alSourcefv(source, AL_VELOCITY, source_velocity);
        alSourcei(source, AL_LOOPING, AL_TRUE);

        alSourcePlay(source);
    }
};

#endif