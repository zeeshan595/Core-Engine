#ifndef _AUDIO_SOURCE
#define _ME_AUDIO_SOURCESH

class AudioSource : public Module
{
public:
    bool play_on_start;

    AudioSource();
    ~AudioSource();

    void Start();
    void Update();
    void LoadAudioFile(std::string filename);

    void Play();
    void Stop();
    void Pause();
    void SetLooping(bool loop);
    void SetPitch(float pitch);
    void SetGain(float gain);
    void Is3DSound(bool is_3D);
    void SetRollOffFactor(float roll);
    void SetReferenceDistance(float distance);

private:
    ALuint source;
    ALuint buffer;

    bool sound3D;
    float roll_off;

    void GenerateOpenALAudio(unsigned char* data, DWORD data_size, DWORD sample_rate, short channels, short bits_per_sample);
};

#include "AudioSource.cpp"

#endif