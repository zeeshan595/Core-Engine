#ifndef _CORE
#define _CORE

#include "../Static/Common.h"

class Core
{
public:
    Core(std::string window_title);
    ~Core();
    void Start();
    void Quit();

private:
    SDL_GLContext context;
    bool is_running = true;
    
    void InitOpenGL();
    void Update();
    void Render();
    void Input(SDL_Event* e);
};

#include "Core.cpp"

#endif