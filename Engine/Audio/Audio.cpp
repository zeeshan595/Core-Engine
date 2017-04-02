glm::vec3           Audio::listener_position;
glm::vec3           Audio::listener_velocity;
ALCdevice*          Audio::al_device;
ALCcontext*         Audio::al_context;

glm::vec3 Audio::GetListenerPosition()
{
    return listener_position;
}
glm::vec3 Audio::GetListenerVelocity()
{
    return listener_velocity;
}

void Audio::ChangeListenerPosition(glm::vec3 pos)
{
    listener_position = pos;
    ALfloat position[]= { pos.x, pos.y, pos.z };
    alListenerfv(AL_POSITION, position);
}

void Audio::ChangeListenerVelocity(glm::vec3 vel)
{
    listener_velocity = vel;
    ALfloat velocity[] = { vel.x, vel.y, vel.z };
    alListenerfv(AL_VELOCITY, velocity);
}

void Audio::ChangeListenerOrientation(glm::vec3 forward, glm::vec3 top)
{
    ALfloat orientation[]  = { 
        forward.x, forward.y, forward.z,
        top.x, top.y, top.z 
    };
    alListenerfv(AL_ORIENTATION, orientation);
}

void Audio::InitAudio()
{
    Audio::al_device = alcOpenDevice(NULL);
    if(!Audio::al_device)
    {
        std::cout << "no sound device" << std::endl;
        return;
    }
    Audio::al_context = alcCreateContext(Audio::al_device, NULL);
    alcMakeContextCurrent(Audio::al_context);
    if (!Audio::al_context)
    {
        std::cout << "no sound context" << std::endl;
        return;
    }
    
    //alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);

    std::cout << "SUCCESS [OpenAL]" << std::endl;
}

void Audio::DestroyAudio()
{
    alcDestroyContext(al_context);
    alcCloseDevice(Audio::al_device);
}