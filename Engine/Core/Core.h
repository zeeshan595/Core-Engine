#ifndef _CORE
#define _CORE

class Core
{
public:
    Core(const char* window_title);
    ~Core();

    void Start();
    void Quit();
    static bool is_running;

private:

    void InitOpenGL();
    void Update();
    void Render();
    void Stop();
};

bool Core::is_running = false;

#include "Core.cpp"
Core engine("Core Engine");
#endif