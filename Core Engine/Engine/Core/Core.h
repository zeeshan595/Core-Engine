#ifndef _CORE
#define _CORE

#include "../Static/Common.h"
#include "Environment.h"
#include "../Modules/Module.h"
#include "../Modules/Mesh.h"


class Core
{
public:
    std::shared_ptr<Environment> environments;

    Core();
    ~Core();
    void Start();
    void ChangeResolution(int w, int h, bool fullscreen);
    void StopEngine(){
        run = false;
    }

private:
    bool run;
    SDL_Window* window;
    SDL_GLContext context;
    float current_time;
    float prev_time;

    void InitOpenGl();
    void Update();
    void Render();
    void Input(SDL_Event* e);
};

#include "Core.cpp"

#endif