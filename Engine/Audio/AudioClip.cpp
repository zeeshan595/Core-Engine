AudioClip::AudioClip(const std::string filename)
{
    fp = fopen((SOUND_PATH + filename).c_str(), "rb");
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
    
    uint32_t counter = 0;
    fread(type,sizeof(char), 1, fp);
    while (type[0] != 'd')
    {
        fread(type,sizeof(char), 1, fp);
        if (counter > 1000)
            break;
        counter++;
    }
    fread(type,sizeof(char), 3, fp);
    if (type[0] != 'a' || type[1] != 't' || type[2] != 'a')
    {
        std::cout << "Missing data" << std::endl;
        return;
    }
    fread(&data_size, sizeof(DWORD), 1, fp);
    data = new unsigned char[data_size];
    fread(data, sizeof(BYTE), data_size, fp);
}

AudioClip::~AudioClip()
{
    delete fp;
    delete data;
}

short AudioClip::GetBitsPerSample()
{
    return bits_per_sample;
}

short AudioClip::GetBytesPerSample()
{
    return bytes_per_sample;
}

short AudioClip::GetFormatType()
{
    return format_type;
}

short AudioClip::GetChannels()
{
    return channels;
}

unsigned char* AudioClip::GetData()
{
    return data;
}

DWORD AudioClip::GetDataSize()
{
    return data_size;
}

DWORD AudioClip::GetSampleRate()
{
    return sample_rate;
}
