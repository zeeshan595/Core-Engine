#ifndef _WORLD
#define _WORLD

#include "Entity.h"
#include "Camera.h"

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

    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Camera>> cameras;
};

#endif