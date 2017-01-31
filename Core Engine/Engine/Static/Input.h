#ifndef _INPUT
#define _INPUT

class Input
{
public:
    static std::map<int, bool> keys_up;
    static std::map<int, bool> keys_down;
    static std::map<int, bool> keys;
    static glm::vec2 mouse_delta;
    static glm::vec2 mouse_position;
};
std::map<int, bool> Input::keys_up;
std::map<int, bool> Input::keys_down;
std::map<int, bool> Input::keys;
glm::vec2 Input::mouse_delta;
glm::vec2 Input::mouse_position;

#endif