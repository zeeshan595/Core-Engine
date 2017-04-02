#ifndef _CAMERA_MOVMENT
#define _CAMERA_MOVMENT

class CameraMovment : public Module
{
public:
    Entity* player_car          = NULL;
    float   camera_position     = 10.0f;
    float   camera_height       = 3.0f;

    void Start()
    {
        player_car = Environment::FindEntity("Car");
    }

    void Update()
    {
        glm::vec3 offset = player_car->transform.Forward() * -camera_position;
        offset.y += camera_height;
        entity->transform.SetPosition(player_car->transform.GetPosition() + offset);
        entity->transform.SetRotation(player_car->transform.GetRotation());
    }
};

#endif