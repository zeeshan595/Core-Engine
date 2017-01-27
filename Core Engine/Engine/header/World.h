#ifndef _WORLD
#define _WORLD

#include "Entity.h"
#include "Camera.h"
#include "Light.h"

class World
{
public:
    std::shared_ptr<Entity> CreateEntity(std::string name)
    {
        std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(name));
        entities.push_back(e);
        return e;
    }
    std::shared_ptr<Camera> CreateCamera()
    {
        std::shared_ptr<Camera> c = std::shared_ptr<Camera>(new Camera());
        cameras.push_back(c);
        return c;
    }
    std::shared_ptr<Light> CreateLight(Light::LIGHT_TYPE light_type)
    {
        std::shared_ptr<Light> l = std::shared_ptr<Light>(new Light(light_type));
        lights.push_back(l);
        return l;
    }

    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Camera>> cameras;
    std::vector<std::shared_ptr<Light>> lights;
};

#endif