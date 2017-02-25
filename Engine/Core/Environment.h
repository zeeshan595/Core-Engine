#ifndef _ENVIRONMENT
#define _ENVIRONMENT

class Environment
{
public:
    Environment(std::string environment_name);
    
    static std::shared_ptr<Skybox> GetSkybox();
    static std::shared_ptr<Entity> FindEntity(std::string name);


    static void ChangeEnvironment(int id);
    static void ChangeEnvironment(std::string environment_name);
    static int  CreateEnvironment(std::string environment_name);
    static int  GetEnvironmentSize();
    static int  GetCurrentEnvironment();

    static std::shared_ptr<Entity> CreateEntity(std::string name);
    static std::shared_ptr<Camera> CreateCamera(std::string name);
    static std::shared_ptr<Light> CreateLight(std::string name);
    static std::vector<std::shared_ptr<Entity>>* GetEntities();
    static std::vector<std::shared_ptr<Camera>>* GetCameras();
    static std::vector<std::shared_ptr<Light>>* GetLights();

    static void StartModules();
    static void StopModules();

private:
    static bool modules_started;
    std::string name;
    std::shared_ptr<Skybox> skybox;

    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Camera>> cameras;
    std::vector<std::shared_ptr<Light>> lights;

    static std::vector<std::shared_ptr<Environment>> environments;
    static int current_environment;
};
bool Environment::modules_started = false;
std::vector<std::shared_ptr<Environment>> Environment::environments;
int Environment::current_environment;

#include "Environment.c"

#endif