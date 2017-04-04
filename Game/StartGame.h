#ifndef _START_GAME
#define _START_GAME

class StartGame : public Module
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