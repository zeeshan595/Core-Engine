#ifndef _MENU_MANAGER
#define _MENU_MANAGER

class MenuManager : public Module
{
public:
    void Update()
    {
        if (Input::GetKeyDown(SDLK_SPACE))
        {
            Environment::SetEnvironment((int32_t)1, true);
        }
    }
};

#endif