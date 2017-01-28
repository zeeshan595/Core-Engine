#ifndef _MODULE
#define _MODULE

#include "../Rendering/Camera.h"
#include "../Rendering/Light.h"

class Entity;
class Module
{
public:
    std::shared_ptr<Entity> attached_to;

    virtual void Update(){}
    virtual void Render(std::shared_ptr<Camera> camera, std::vector<std::shared_ptr<Light>> lights){}
    virtual void Input(SDL_Event* e){}
};

#endif