#ifndef _AUDIO
#define _AUDIO

class Audio
{
public:
    static glm::vec3 GetListenerPosition();
    static glm::vec3 GetListenerVelocity();
    static void ChangeListenerPosition(glm::vec3 pos);    
    static void ChangeListenerVelocity(glm::vec3 vel);
    static void ChangeListenerOrientation(glm::vec3 forward, glm::vec3 top);
    static void InitAudio();
    static void DestroyAudio();

private:
    static glm::vec3 listener_position;
    static glm::vec3 listener_velocity;
    static ALCdevice* al_device;
    static ALCcontext* al_context;
};
glm::vec3 Audio::listener_position;
glm::vec3 Audio::listener_velocity;
ALCdevice* Audio::al_device;
ALCcontext* Audio::al_context;

#include "Audio.c"

#endif