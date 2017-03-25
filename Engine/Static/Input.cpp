std::map<uint32_t, bool>        Input::keys_up;
std::map<uint32_t, bool>        Input::keys_down;
std::map<uint32_t, bool>        Input::keys;

std::map<uint8_t, bool>         Input::mouse_down;
std::map<uint8_t, bool>         Input::mouse_up;
std::map<uint8_t, bool>         Input::mouse;
glm::vec2                       Input::mouse_delta;
glm::vec2                       Input::mouse_position;
glm::vec2                       Input::global_mouse_position;
glm::vec2                       Input::mouse_wheel;

bool Input::UpdateInputs(SDL_Event* e)
{
    keys_down.clear();
    keys_up.clear();
    mouse_down.clear();
    mouse_up.clear();
    mouse_wheel = glm::vec2(0, 0);
    
    //Update Mouse Input
    int32_t x, y;
    SDL_GetMouseState(&x, &y);
    mouse_position = glm::vec2(x, y);
    SDL_GetRelativeMouseState(&x, &y);
    mouse_delta = glm::vec2(x, y);
    SDL_GetGlobalMouseState(&x, &y);
    global_mouse_position = glm::vec2(x, y);

    while (SDL_PollEvent(e))
    {
        if (e->key.repeat == 0){
            switch(e->type)
            {
                case SDL_QUIT:
                case SDL_WINDOWEVENT_CLOSE:
                    return false;
                    break;

                case SDL_KEYDOWN:
                    keys_down[e->key.keysym.sym] = true;
                    keys[e->key.keysym.sym] = true;
                    break;
                case SDL_KEYUP:
                    keys_up[e->key.keysym.sym] = true;
                    keys[e->key.keysym.sym] = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse_down[e->button.button] = true;
                    mouse[e->button.button] = true;
                    break;
                case SDL_MOUSEBUTTONUP:
                    mouse_up[e->button.button] = true;
                    mouse[e->button.button] = false;
                    break;
                case SDL_MOUSEWHEEL:
                    mouse_wheel = glm::vec2(e->wheel.x, e->wheel.y);
                    break;
            }
        }
    }

    return true;
}

bool Input::GetKeyUp(uint32_t key)
{
    return keys_up[key];
}
bool Input::GetKeyDown(uint32_t key)
{
    return keys_down[key];
}
bool Input::GetKey(uint32_t key)
{
    return keys[key];
}

bool Input::GetMouseUp(uint32_t key)
{
    return mouse_up[key];
}
bool Input::GetMouseDown(uint32_t key)
{
    return mouse_down[key];
}
bool Input::GetMouseKey(uint32_t key)
{
    return mouse[key];
}
glm::vec2 Input::GetMouseDelta()
{
    return mouse_delta;
}
glm::vec2 Input::GetMousePosition()
{
    return mouse_position;
}
glm::vec2 Input::GetGlobalMousePosition()
{
    return global_mouse_position;
}
glm::vec2 Input::GetMouseWheel()
{
    return mouse_wheel;
}