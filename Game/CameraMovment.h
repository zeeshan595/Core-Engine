#ifndef _CAMERA_MOVMENT
#define _CAMERA_MOVMENT

class CameraMovment : public Module
{
public:
    AudioSource*    audio               = NULL;
    Entity*         player_car          = NULL;
    float           camera_position     = 15.0f;
    float           camera_height       = 7.0f;

    void Start()
    {
        player_car  = Environment::FindEntity("Car");
        audio       = entity->GetModule<AudioSource>();
    }

    void Update()
    {
        glm::vec3 offset = player_car->transform.Forward() * -camera_position;
        offset.y = camera_height;
        //offset -= player_car->transform.Right() * 0.5f;
        entity->transform.SetPosition(LerpPosition(entity->transform.GetPosition(), player_car->transform.GetPosition() + offset, Time::delta_time * 5.0f));
        glm::vec3 rotation = glm::vec3(0, player_car->transform.EulerAngles().y, 0);
        if (player_car->transform.EulerAngles().x != 0)
            rotation.y = -rotation.y + 3.14f;

        //rotation.y -= 0.3f;
        //rotation.z -= 0.10f;
        entity->transform.Rotate(rotation);

        if (Input::GetKeyDown(SDLK_m))
        {
            GameResources::mute_sounds = !GameResources::mute_sounds;
            if (GameResources::mute_sounds)
            {
                audio->Pause();
            }
            else
            {
                audio->Play();
            }
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