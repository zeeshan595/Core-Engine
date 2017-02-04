#ifndef _AUDIO_SOURCE
#define _AUDIO_SOURCE

class AudioSource : public Module
{
public:
    bool play_on_start;

    AudioSource();
    ~AudioSource();

    void Start();
    void Update();
    void SetClip(std::shared_ptr<AudioClip> clip);
    std::shared_ptr<AudioClip> GetClip();

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
    std::shared_ptr<AudioClip> audio_clip;
    ALuint source;
    ALuint buffer;

    bool sound3D;
    float roll_off;
};

#include "AudioSource.cpp"

#endif