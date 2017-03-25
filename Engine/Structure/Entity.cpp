Entity::Entity(const char* name)
{
    this->name = name;
    transform = Transform();
    layer = 0;
    modules.clear();
}
Entity::~Entity()
{
    for (uint32_t i = 0; i < modules.size(); i++)
    {
        delete modules[i];
    }
    modules.clear();
}

void Entity::SetName(std::string name)
{
    this->name = name;
}
void Entity::SetLayer(uint32_t layer)
{
    this->layer = layer;
}

std::string             Entity::GetName()
{
    return name;
}
uint32_t                Entity::GetLayer()
{
    return layer;
}
std::vector<Module*>*    Entity::GetModules()
{
    return &modules;
}

template<typename T>    T*      Entity::CreateModule()
{
    if (GetModule<T>() != NULL)
    {
        std::cout << "WARNING: Entitiy " << name << " tried to add multiple modules of the same type." << std::endl;
        return NULL;
    }
    T* t_module = new T();
    Module* m = dynamic_cast<Module*>(t_module);
    m->entity = this;
    modules.push_back(m);
    return t_module;
}
template<typename T>    T*      Entity::GetModule()
{
    for (uint32_t i = 0; i < modules.size(); i++)
    {
        if (dynamic_cast<T*>(modules[i]) != nullptr)
        {
            return dynamic_cast<T*>(modules[i]);
        }
    }
}
template<typename T>    void    Entity::DestroyModule()
{
    for (uint32_t i = 0; i < modules.size(); i++)
    {
        if (dynamic_cast<T*>(modules[i]) != nullptr)
        {
            modules.erase(modules.begin() + i);
            return;
        }
    }
}