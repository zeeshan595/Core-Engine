std::vector<Environment*>       Environment::environments;
uint32_t                        Environment::current_environment        = -1;

Environment::Environment(const char* name)
{
    this->name = name;
}
Environment::~Environment()
{
    for (uint32_t i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
    entities.clear();
}

Entity*      Environment::CreateEntity            (const char* name)
{
    Entity* e = new Entity(name);
    environments[current_environment]->entities.push_back(e);
    return e;
}
Camera*     Environment::CreateCamera             (const char* name)
{
    Camera* e = new Camera(name);
    environments[current_environment]->entities.push_back(dynamic_cast<Entity*>(e));
    environments[current_environment]->cameras.push_back(e);
    return e;
}
Light*      Environment::CreateLight              (const char* name)
{
    Light* e = new Light(name);
    environments[current_environment]->entities.push_back(dynamic_cast<Entity*>(e));
    environments[current_environment]->lights.push_back(e);
    return e;
}
Environment* Environment::CreateEnvironment       (const char* name)
{
    Environment* e = new Environment(name);
    environments.push_back(e);
    current_environment = environments.size() - 1;
    return e;
}
void         Environment::DestroyEntity           (Entity* entity)
{
    for (uint32_t i = 0; i < environments[current_environment]->entities.size(); i++)
    {
        if (environments[current_environment]->entities[i] == entity)
        {
            environments[current_environment]->entities.erase(environments[current_environment]->entities.begin() + i);
            delete entity;
            return;
        }
    }
}
void         Environment::DestroyEnvironment      (Environment* environment)
{
    std::vector<Entity*> entitites = (*environment->GetEntities());
    for (uint32_t i = 0; i < entitites.size(); i++)
    {
        delete entitites[i];
    }
    entitites.clear();
    (*environment->GetCameras()).clear();
    (*environment->GetLights()).clear();
    for (uint32_t i = 0; i < environments.size(); i++)
    {
        if (environments[i] == environment && i != current_environment)
        {
            environments.erase(environments.begin() + i);
            delete environment;
            return;
        }
    }
}

uint32_t     Environment::GetEnvironmentSize      ()
{
    return environments.size();
}

uint32_t     Environment::GetCurrentEnvironment   ()
{
    return current_environment;
}

void         Environment::SetEnvironment          (Environment* environment)
{
    if (current_environment != -1)
        StopModules();

    for (uint32_t i = 0; i < environments.size(); i++)
    {
        if (environments[i] == environment)
        {
            current_environment = i;
            return;
        }
    }

    StartModules();
}

std::vector<Entity*>*   Environment::GetEntities()
{
    return &environments[current_environment]->entities;
}
std::vector<Camera*>*   Environment::GetCameras()
{
    return &environments[current_environment]->cameras;
}
std::vector<Light*>*    Environment::GetLights()
{
    return &environments[current_environment]->lights;
}

void                     Environment::SetSkybox(Skybox* skybox)
{
    environments[current_environment]->skybox = skybox;
}
Skybox*                  Environment::GetSkybox()
{
    return environments[current_environment]->skybox;
}

void Environment::StartModules()
{
    Environment::GetSkybox()->Start();
    std::vector<Entity*> entities = environments[current_environment]->entities;
    for (uint32_t i = 0; i < entities.size(); i++)
    {
        std::vector<Module*> modules = (*entities[i]->GetModules());
        for (uint32_t j = 0; j < modules.size(); j++)
        {
            modules[j]->Start();
        }
    }
}

void Environment::StopModules()
{
    Environment::GetSkybox()->Stop();
    std::vector<Entity*> entities = environments[current_environment]->entities;
    for (uint32_t i = 0; i < entities.size(); i++)
    {
        std::vector<Module*> modules = (*entities[i]->GetModules());
        for (uint32_t j = 0; j < modules.size(); j++)
        {
            modules[j]->Stop();
        }
    }
}