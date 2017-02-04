#ifndef _AUDIO_CLIP
#define _AUDIO_CLIP

class AudioClip
{
public:
    

    AudioClip(const std::string filename);
    ~AudioClip();
    
    short GetBitsPerSample();
    short GetBytesPerSample();
    short GetFormatType();
    short GetChannels();
    unsigned char* GetData();
    DWORD GetDataSize();
    DWORD GetSampleRate();

private:
    FILE* fp = NULL;
    char type[4];
    DWORD size, chunk_size;
    short format_type, channels;
    DWORD sample_rate, average_bytes_per_second;
    short bytes_per_sample, bits_per_sample;
    DWORD data_size;
    unsigned char* data;
};

#include "AudioClip.cpp"

#endif