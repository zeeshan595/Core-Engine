#ifndef _ENVIRONMENT
#define _ENVIRONMENT

class Environment
{
public:
    static std::vector<std::shared_ptr<Environment>> environments;
    static int current_environment;
    std::string name;
    std::shared_ptr<Skybox> skybox;

    Environment(std::string environment_name){
        name = environment_name;
        skybox = std::shared_ptr<Skybox>(new Skybox());
    }
    static std::shared_ptr<Skybox> GetSkybox(){
        int environment_id = Environment::current_environment;
        return Environment::environments[environment_id]->skybox;
    }
    static std::shared_ptr<Entity> FindEntity(std::string name){
        int environment_id = Environment::current_environment;
        for (int i = 0; i < Environment::environments[environment_id]->entities.size(); i++){
            if (Environment::environments[environment_id]->entities[i]->name == name){
                return Environment::environments[environment_id]->entities[i];
            }
        }
    }
    static void ChangeEnvironment(int id){
        current_environment = id;
    }
    static int CreateEnvironment(std::string environment_name){
        environments.push_back(std::shared_ptr<Environment>(new Environment(environment_name)));
        return environments.size() - 1;
    }
    static std::shared_ptr<Entity> CreateEntity(std::string name){
        int environment_id = Environment::current_environment;
        std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(name));
        Environment::environments[environment_id]->entities.push_back(e);
        return e;
    }
    static std::shared_ptr<Camera> CreateCamera(std::string name){
        int environment_id = Environment::current_environment;
        std::shared_ptr<Camera> e = std::shared_ptr<Camera>(new Camera(name));
        Environment::environments[environment_id]->cameras.push_back(e);
        return e;
    }
    static std::shared_ptr<Light> CreateLight(std::string name){
        int environment_id = Environment::current_environment;
        std::shared_ptr<Light> e = std::shared_ptr<Light>(new Light(name));
        Environment::environments[environment_id]->lights.push_back(e);
        return e;
    }

    static std::vector<std::shared_ptr<Entity>>* GetEntities(){
        int environment_id = Environment::current_environment;
        return &Environment::environments[environment_id]->entities;
    }
    static std::vector<std::shared_ptr<Camera>>* GetCameras(){
        int environment_id = Environment::current_environment;
        return &Environment::environments[environment_id]->cameras;
    }
    static std::vector<std::shared_ptr<Light>>* GetLights(){
        int environment_id = Environment::current_environment;
        return &Environment::environments[environment_id]->lights;
    }
private:
    std::vector<std::shared_ptr<Entity>> entities;
    std::vector<std::shared_ptr<Camera>> cameras;
    std::vector<std::shared_ptr<Light>> lights;
};
int Environment::current_environment = 0;
std::vector<std::shared_ptr<Environment>> Environment::environments;

#endif