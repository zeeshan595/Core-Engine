std::vector<Environment*>       Environment::environments;
int32_t                         Environment::current_environment        = -1;

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
    delete skybox;
    delete name;
}

void         Environment::CleanUp()
{
    StopModules();
    for (uint32_t i = 0; i < environments.size(); i++)
    {
        delete environments[current_environment];
    }
    environments.clear();
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
    return e;
}

Entity*      Environment::FindEntity              (const char* name)
{
    std::vector<Entity*> ent = environments[current_environment]->entities;
    for (uint32_t i = 0; i < ent.size(); i++)
    {
        if (ent[i]->GetName() == name)
        {
            return ent[i];
        }
    }
}

uint32_t     Environment::GetEnvironmentSize      ()
{
    return environments.size();
}

Environment* Environment::GetCurrentEnvironment   ()
{
    return environments[current_environment];
}

uint32_t     Environment::GetCurrentEnvironmentID ()
{
    return current_environment;
}

void         Environment::SetEnvironment          (Environment* environment, bool start_modules)
{
    int32_t environment_id = -1;
    for (int32_t i = 0; i < environments.size(); i++)
    {
        if (environments[i] == environment)
        {
            environment_id = i;
            break;
        }
    }
    if (environment_id == -1)
    {
        throw std::runtime_error("ERROR [SetEnvironment]: could not find environment");
    }

    SetEnvironment((uint32_t)environment_id, start_modules);
}

void         Environment::SetEnvironment          (int32_t environment_id  , bool start_modules)
{
    if (start_modules)
    {
        if (current_environment != -1)
            StopModules();
    }
    current_environment = environment_id;
    if (start_modules)
    {
        StartModules();
    }
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
    if (Environment::GetSkybox() != NULL)
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
    if (Environment::GetSkybox() != NULL)
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