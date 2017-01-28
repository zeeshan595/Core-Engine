#ifndef _CORE
#define _CORE

#include "../Static/Common.h"
#include "World.h"
#include "../Modules/Module.h"
#include "../Modules/Mesh.h"
#include "../Static/OBJLoader.h"

class Core
{
public:
    std::shared_ptr<World> world;

    Core();
    ~Core();
    void Start();
    void ChangeResolution(int w, int h, bool fullscreen);

private:
    SDL_Window* window;
    SDL_GLContext context;
    float current_time;
    float prev_time;

    void InitOpenGl();
    void Update();
    void Render();
    void Input(SDL_Event* e);

    bool isFullScreen;
};

#include "Core.cpp"

#endif