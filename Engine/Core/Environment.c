Environment::Environment(std::string environment_name)
{
    name = environment_name;
    skybox = std::shared_ptr<Skybox>(new Skybox());
}

std::shared_ptr<Skybox> Environment::GetSkybox()
{
    return Environment::environments[Environment::current_environment]->skybox;
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
    Environment::current_environment = id;
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

std::shared_ptr<Entity> Environment::CreateEntity(std::string name)
{
    std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(name));
    Environment::environments[Environment::current_environment]->entities.push_back(e);
    return e;
}
std::shared_ptr<Camera> Environment::CreateCamera(std::string name)
{
    std::shared_ptr<Camera> e = std::shared_ptr<Camera>(new Camera(name));
    Environment::environments[Environment::current_environment]->cameras.push_back(e);
    return e;
}
std::shared_ptr<Light> Environment::CreateLight(std::string name)
{
    std::shared_ptr<Light> e = std::shared_ptr<Light>(new Light(name));
    Environment::environments[Environment::current_environment]->lights.push_back(e);
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