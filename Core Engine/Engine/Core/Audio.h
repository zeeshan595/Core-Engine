#ifndef _AUDIO
#define _AUDIO

class Audio
{
public:
    static glm::vec3 GetListenerPosition()
    {
        return listener_position;
    }
    static glm::vec3 GetListenerVelocity()
    {
        return listener_velocity;
    }

    static void ChangeListenerPosition(glm::vec3 pos)
    {
        listener_position = pos;
        ALfloat position[]= { pos.x, pos.y, pos.z };
        alListenerfv(AL_POSITION, position);
    }
    
    static void ChangeListenerVelocity(glm::vec3 vel)
    {
        listener_velocity = vel;
        ALfloat velocity[] = { vel.x, vel.y, vel.z };
        alListenerfv(AL_VELOCITY, velocity);
    }

    static void ChangeListenerOrientation(glm::vec3 forward, glm::vec3 top)
    {
        ALfloat orientation[]  = { 
            forward.x, forward.y, forward.z,
            top.x, top.y, top.z 
        };
        alListenerfv(AL_ORIENTATION, orientation);
    }
private:
    static glm::vec3 listener_position;
    static glm::vec3 listener_velocity;
};
glm::vec3 Audio::listener_position;
glm::vec3 Audio::listener_velocity;

#endif