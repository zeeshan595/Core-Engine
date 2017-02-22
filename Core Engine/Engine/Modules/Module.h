#ifndef _MODULE
#define _MODULE

class Entity;
class Camera;
class Light;
class Module
{
public:
    std::shared_ptr<Entity> attached_to;

    virtual void Start(){}
    virtual void Stop(){}
    virtual void Update(){}
    virtual void Render(std::shared_ptr<Camera> rendering_camera){}
};

#endif