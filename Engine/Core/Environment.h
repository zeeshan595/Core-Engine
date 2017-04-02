#ifndef _ENVIRONMENT
#define _ENVIRONMENT

class Core;
class Environment
{
public:
    Environment(const char* name);
    ~Environment();

    static void         CleanUp();

    static Entity*      CreateEntity            (const char* name);
    static Camera*      CreateCamera            (const char* name);
    static Light*       CreateLight             (const char* name);

    static Environment* CreateEnvironment       (const char* name);

    static Entity*      FindEntity              (const char* name);
    static uint32_t     GetEnvironmentSize      ();
    static Environment* GetCurrentEnvironment   ();
    static uint32_t     GetCurrentEnvironmentID ();
    static void         SetEnvironment          (Environment* environment, bool start_modules);
    static void         SetEnvironment          (int32_t environment_id  , bool start_modules);

    static std::vector<Entity*>*    GetEntities();
    static std::vector<Camera*>*    GetCameras();
    static std::vector<Light*>*     GetLights();
    
    static void                     SetSkybox(Skybox* skybox);
    static Skybox*                  GetSkybox();
    
private:

    static void    StartModules();
    static void    StopModules();

    const char*                             name                    = NULL;
    Skybox*                                 skybox                  = NULL;
    std::vector<Entity*>                    entities;
    std::vector<Camera*>                    cameras;
    std::vector<Light*>                     lights;

    static std::vector<Environment*>        environments;
    static int32_t                          current_environment;

};

#include "Environment.cpp"
#endif