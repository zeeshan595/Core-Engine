#ifndef _ENTITY
#define _ENTITY

class Entity
{
public:
    Transform               transform;
    
    Entity(const char* name);
    ~Entity();

    void SetName(std::string name);
    void SetLayer(uint32_t layer);

    std::string             GetName();
    uint32_t                GetLayer();
    std::vector<Module*>*   GetModules();

    template<typename T>    T*      CreateModule();
    template<typename T>    T*      GetModule();
    template<typename T>    void    DestroyModule();

protected:
    std::string             name;
    uint32_t                layer           = 0;
    std::vector<Module*>    modules;
};

#include "Entity.cpp"
#endif