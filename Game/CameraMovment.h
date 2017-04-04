#ifndef _CAMERA_MOVMENT
#define _CAMERA_MOVMENT

class CameraMovment : public Module
{
public:
    AudioSource* audio = NULL;
    Entity* player = NULL;
    float   camera_position = 13.0f;
    float   camera_height = 7.0f;
    bool mute = false;

    void Start()
    {
        player = Environment::FindEntity("Player");
        audio = entity->GetModule<AudioSource>();
    }

    void Update()
    {
        glm::vec3 offset = player->transform.Forward() * -camera_position;
         offset.y = camera_height;
        entity->transform.SetPosition(LerpPosition(entity->transform.GetPosition(), player->transform.GetPosition() + offset, Time::delta_time * 5.0f));
        glm::vec3 rotation = glm::vec3(0, player->transform.EulerAngles().y, 0);
        if (player->transform.EulerAngles().x != 0)
            rotation.y = -rotation.y + 3.14f;

        rotation.y -= 0.3f;
        rotation.z -= 0.10f;
        entity->transform.Rotate(rotation);
        
        //Toggle Sound
        if (Input::GetKeyDown(SDLK_q))
        {
            mute =! mute;

            if (mute)
            {
                audio->Pause();
            }
            else
            {
                audio->Play();
            }
        }

        //Toggle Sound
        if (Input::GetKeyDown(SDLK_m))
        {
            mute =! mute;

            if (mute)
            {
                audio->Pause();
            }
            else
            {
                audio->Play();
            }
        }

           
         //End Game
        if (Input::GetKeyDown(SDLK_ESCAPE))
        {   
            audio->Stop();
            AudioClip* end_music_clip = new AudioClip("gameover.wav");
            audio->SetClip(end_music_clip);
            audio->Play();
            Core::is_running = false;
        }
    }

private:
    glm::vec3 LerpPosition(glm::vec3 current, glm::vec3 required, float amount)
    {
        glm::vec3 required_vector = required - current;
        required_vector *= amount;
        return current + required_vector;
    }
};


#endif