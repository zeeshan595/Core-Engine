#ifndef _CORE
#define _CORE

class Core
{
public:
    Core(std::string window_title);
    ~Core();
    void Start();
    void Quit();

    void EnableDebugMode();
    void DisableDebugMode();
    bool IsDebugingEnabled();

private:
    SDL_GLContext context;
    bool is_running = true;
    bool is_debuging = false;
    int active_scene;
    
    void InitOpenGL();
    void Update();
    void Render();
    void Input(SDL_Event* e);
};

#include "Core.c"

#endif