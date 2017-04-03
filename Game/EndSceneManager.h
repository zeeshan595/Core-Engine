#ifndef _END_SCENE
#define _END_SCENE

class EndSceneManager : public Module
{
public:
    void Update()
    {
        if (Input::GetKeyDown(SDLK_SPACE))
        {
            engine.Quit();
        }
    }
};

#endif