Environment::Environment(std::string environment_name)
{
    name = environment_name;
    skybox = std::shared_ptr<Skybox>(new Skybox());
}

std::shared_ptr<Skybox> Environment::GetSkybox(int scene_id)
{
    return Environment::environments[scene_id]->skybox;
}

std::shared_ptr<Entity> Environment::FindEntity(std::string name){
    for (int i = 0; i < Environment::environments[Environment::current_environment]->entities.size(); i++){
        if (Environment::environments[Environment::current_environment]->entities[i]->name == name){
            return Environment::environments[Environment::current_environment]->entities[i];
        }
    }
}
void Environment::ChangeEnvironment(int id)
{
    if (modules_started)
        Environment::StopModules();
    Environment::current_environment = id;
    Environment::StartModules();
}
void Environment::ChangeEnvironment(std::string environment_name)
{
    for (int i = 0; i < environments.size(); i++)
    {
        if (environments[i]->name == environment_name)
        {
            Environment::current_environment = i;
        }
    }
}

int Environment::CreateEnvironment(std::string environment_name)
{
    for (int i = 0; i < environments.size(); i++)
    {
        if (environments[i]->name == environment_name)
        {
            std::cout << "ERROR [CreateEnvironment]: environment already exists with the same name" << std::endl;
            return -1;
        }
    }

    Environment::environments.push_back(std::shared_ptr<Environment>(new Environment(environment_name)));
    return environments.size() - 1;
}
int Environment::GetEnvironmentSize()
{
    return Environment::environments.size();
}
int Environment::GetCurrentEnvironment()
{
    return Environment::current_environment;
}

std::shared_ptr<Entity> Environment::CreateEntity(std::string name, int scene_id)
{
    std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(name));
    Environment::environments[scene_id]->entities.push_back(e);
    return e;
}
std::shared_ptr<Camera> Environment::CreateCamera(std::string name, int scene_id)
{
    std::shared_ptr<Camera> e = std::shared_ptr<Camera>(new Camera(name));
    Environment::environments[scene_id]->cameras.push_back(e);
    return e;
}
std::shared_ptr<Light> Environment::CreateLight(std::string name, int scene_id)
{
    std::shared_ptr<Light> e = std::shared_ptr<Light>(new Light(name));
    Environment::environments[scene_id]->lights.push_back(e);
    return e;
}

std::vector<std::shared_ptr<Entity>>* Environment::GetEntities()
{
    return &Environment::environments[Environment::current_environment]->entities;
}

std::vector<std::shared_ptr<Camera>>* Environment::GetCameras()
{
    return &Environment::environments[Environment::current_environment]->cameras;
}

std::vector<std::shared_ptr<Light>>* Environment::GetLights()
{
    return &Environment::environments[Environment::current_environment]->lights;
}

void Environment::StartModules()
{
    modules_started = true;
    //Before starting reorder camera using draw order
    std::sort((*Environment::GetCameras()).begin(), (*Environment::GetCameras()).end(), Camera::CameraOrder);

    //Cameras
    for (auto i = (*Environment::GetCameras()).begin(); i != (*Environment::GetCameras()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Start();
        }
    }
    //Lights
    for (auto i = (*Environment::GetLights()).begin(); i != (*Environment::GetLights()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Start();
        }
    }
    //Entities
    for (auto i = (*Environment::GetEntities()).begin(); i != (*Environment::GetEntities()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Start();
        }
    }
}

void Environment::StopModules()
{
    //Cameras
    for (auto i = (*Environment::GetCameras()).begin(); i != (*Environment::GetCameras()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Stop();
        }
    }
    //Lights
    for (auto i = (*Environment::GetLights()).begin(); i != (*Environment::GetLights()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Stop();
        }
    }
    //Entities
    for (auto i = (*Environment::GetEntities()).begin(); i != (*Environment::GetEntities()).end(); ++i)
    {
        for (std::shared_ptr<Module> module : (*i)->GetModules())
        {
            module->Stop();
        }
    }
}