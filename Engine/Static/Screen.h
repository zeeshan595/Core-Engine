#ifndef _SCREEN
#define _SCREEN

class Screen
{
public:
    static void InitWindow(const char* title);
    static void DestroyWindow();

    static void SetWindowTitle          (const char* title);
    static void SetResolution           ( uint32_t w        , uint32_t h           , bool full_screen   );
    static void SetScreenPosition       ( uint32_t x        , uint32_t y           );
    static void GetDisplayResolution    ( uint32_t &width   , uint32_t &height     );
    static void GetWindowPosition       ( uint32_t &x       , uint32_t &y          );
    static void LockCursor              ( bool lock );

    static SDL_Window*        GetWindow();
    static SDL_GLContext      GetContext();

private:
    static SDL_Window*          window;
    static SDL_GLContext        context;
    static bool                 is_fullscreen;
    static uint32_t             WIDTH;
    static uint32_t             HEIGHT;

};

#include "Screen.cpp"
#endif