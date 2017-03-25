#ifndef _INPUT
#define _INPUT

class Input
{
public:
    static bool UpdateInputs(SDL_Event* e);

    static bool GetKeyUp        (uint32_t key);
    static bool GetKeyDown      (uint32_t key);
    static bool GetKey          (uint32_t key);

    static bool GetMouseUp      (uint32_t key);
    static bool GetMouseDown    (uint32_t key);
    static bool GetMouseKey     (uint32_t key);
    static glm::vec2 GetMouseDelta();
    static glm::vec2 GetMousePosition();
    static glm::vec2 GetGlobalMousePosition();
    static glm::vec2 GetMouseWheel();

private:
    static std::map<uint32_t, bool>         keys_up;
    static std::map<uint32_t, bool>         keys_down;
    static std::map<uint32_t, bool>         keys;

    static std::map<uint8_t, bool>          mouse_down;
    static std::map<uint8_t, bool>          mouse_up;
    static std::map<uint8_t, bool>          mouse;
    static glm::vec2                        mouse_delta;
    static glm::vec2                        mouse_position;
    static glm::vec2                        global_mouse_position;
    static glm::vec2                        mouse_wheel;

};

#include "Input.cpp"
#endif