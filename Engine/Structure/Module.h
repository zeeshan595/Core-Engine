#ifndef _MODULE
#define _MODULE

class Entity;
class Camera;
class Module
{
public:
    Entity* entity;

    virtual void Start(){}
    virtual void Stop(){}
    virtual void Update(){}
    virtual void Render(Camera* rendering_camera){}
};

#endif