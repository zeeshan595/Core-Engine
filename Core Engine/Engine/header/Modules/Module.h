#ifndef _MODULE
#define _MODULE

#include "../Camera.h"

class Entity;
class Module
{
public:
    std::shared_ptr<Entity> attached_to;

    virtual void Update(){}
    virtual void Render(std::shared_ptr<Camera> camera){}
    virtual void Input(SDL_Event* e){}
};

#endif