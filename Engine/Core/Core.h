#ifndef _CORE
#define _CORE

class Core
{
public:
    Core(const char* window_title);
    ~Core();

    void Start();
    void Quit();

private:
    bool is_running = false;

    void Update();
    void Stop();
};

#include "Core.cpp"
Core engine("Core Engine");
#endif