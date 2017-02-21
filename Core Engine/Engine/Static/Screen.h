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

    static void SetResolution(int w, int h, bool full_screen){
        Screen::width = w;
        Screen::height = h;
        SDL_SetWindowSize(Screen::window, Screen::width, Screen::height);
        if (full_screen)
            SDL_SetWindowFullscreen(Screen::window, SDL_TRUE);
        else
            SDL_SetWindowFullscreen(Screen::window, SDL_FALSE);
    }
    static void SetScreenPosition(int x, int y){
        SDL_SetWindowPosition(Screen::window, x, y);
    }
    static glm::vec2 GetDisplayResolution(){
        SDL_DisplayMode current;
        int should_be_zero = SDL_GetCurrentDisplayMode(0, &current);
        if (should_be_zero != 0){
            std::cout << "WARNING (GetDisplayResolution): Could not find monitor" << std::endl;
            return glm::vec2(0, 0);
        }
        return glm::vec2(current.w, current.h);
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