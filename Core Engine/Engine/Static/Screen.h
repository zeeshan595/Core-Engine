#ifndef _SCREEN
#define _SCREEN

class Screen
{
public:
    static SDL_Window* window;
    static bool is_fullscreen;
    static int width;
    static int height;
    static int draw_calls;

    static void ChangeResolution(int w, int h, bool full_screen)
    {
        Screen::width = w;
        Screen::height = h;
        SDL_SetWindowSize(Screen::window, Screen::width, Screen::height);
        if (full_screen)
            SDL_SetWindowFullscreen(Screen::window, SDL_TRUE);
        else
            SDL_SetWindowFullscreen(Screen::window, SDL_FALSE);
    }

    static glm::vec2 GetWindowPosition(){
        int x, y;
        SDL_GetWindowPosition(Screen::window, &x, &y);
        return glm::vec2(static_cast<float>(x), static_cast<float>(y));
    }
    
    static bool IsWindowFocused(){
        return SDL_GetMouseFocus() == Screen::window;
    }
};
int Screen::width = 1024;
int Screen::height = 720;
bool Screen::is_fullscreen = false;
SDL_Window* Screen::window;
int Screen::draw_calls;

#endif