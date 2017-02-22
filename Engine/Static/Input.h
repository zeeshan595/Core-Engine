#ifndef _INPUT
#define _INPUT

class Input
{
public:
    static std::map<int, bool> keys_up;
    static std::map<int, bool> keys_down;
    static std::map<int, bool> keys;

    static std::map<Uint8, bool> mouse_down;
    static std::map<Uint8, bool> mouse_up;
    static std::map<Uint8, bool> mouse;
    static glm::vec2 mouse_delta;
    static glm::vec2 mouse_position;
    static glm::vec2 global_mouse_position;
    static glm::vec2 mouse_wheel;

    static void LockCursor(bool lock){
        if (lock)
            SDL_SetRelativeMouseMode(SDL_TRUE);
        else
            SDL_SetRelativeMouseMode(SDL_FALSE);
    }
};
std::map<int, bool> Input::keys_up;
std::map<int, bool> Input::keys_down;
std::map<int, bool> Input::keys;

std::map<Uint8, bool> Input::mouse_down;
std::map<Uint8, bool> Input::mouse_up;
std::map<Uint8, bool> Input::mouse;
glm::vec2 Input::mouse_delta;
glm::vec2 Input::mouse_position;
glm::vec2 Input::mouse_wheel;
glm::vec2 Input::global_mouse_position;

#endif