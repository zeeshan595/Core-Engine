#ifndef _GAME_OVER
#define _GAME_OVER

class GameOver : public Module
{
public:

    int counter = 5;

    void Start()
    {
    }

    void update()
    {
        counter--;
        if(counter == 0)
        {
            
            Core::is_running = false;
        }
    }

       
};

#endif