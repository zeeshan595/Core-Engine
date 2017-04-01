#ifndef _ENVIRONMENT
#define _ENVIRONMENT

class Core;
class Environment
{
public:
    Environment(const char* name);
    ~Environment();

    static Entity*      CreateEntity            (const char* name);
    static Camera*      CreateCamera            (const char* name);
    static Light*       CreateLight             (const char* name);

    static Environment* CreateEnvironment       (const char* name);

    static void         DestroyEntity           (Entity* entity);
    static void         DestroyCamera           (Camera* camera);
    static void         DestroyEnvironment      (Environment* environment);

    static uint32_t     GetEnvironmentSize      ();
    static uint32_t     GetCurrentEnvironment   ();
    static void         SetEnvironment          (Environment* environment, bool start_modules);

    static std::vector<Entity*>*    GetEntities();
    static std::vector<Camera*>*    GetCameras();
    static std::vector<Light*>*     GetLights();
    
    static void                     SetSkybox(Skybox* skybox);
    static Skybox*                  GetSkybox();
    
private:

    static void    StartModules();
    static void    StopModules();

    const char*                             name;
    Skybox*                                 skybox;
    std::vector<Entity*>                    entities;
    std::vector<Camera*>                    cameras;
    std::vector<Light*>                     lights;

    static std::vector<Environment*>        environments;
    static uint32_t                         current_environment;

};

#include "Environment.cpp"
#endif