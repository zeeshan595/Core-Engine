#ifndef _AUDIO
#define _AUDIO

class Audio
{
public:
    static void InitAudio();
    static void DestroyAudio();

    static glm::vec3 GetListenerPosition();
    static glm::vec3 GetListenerVelocity();
    static void ChangeListenerPosition(glm::vec3 pos);    
    static void ChangeListenerVelocity(glm::vec3 vel);
    static void ChangeListenerOrientation(glm::vec3 forward, glm::vec3 top);

private:
    static glm::vec3        listener_position;
    static glm::vec3        listener_velocity;
    static ALCdevice*       al_device;
    static ALCcontext*      al_context;
};

#include "Audio.cpp"
#endif