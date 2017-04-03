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
        entity->transform.SetPosition(LerpPosition(entity->transform.GetPosition(), player_car->transform.GetPosition() + offset, Time::delta_time * 5.0f));
        entity->transform.SetRotation(player_car->transform.GetRotation());
    }

    void Render(Camera* rendering_camera)
    {
        //Debuging For Bullet Physics
        glm::vec3 camera_pos    = entity->transform.GetPosition() * 20.0f;
        glm::vec3 cam_rot       = entity->transform.EulerAngles();
        glLoadIdentity();
        glTranslatef(-camera_pos.x, -camera_pos.y, -camera_pos.z);
        glRotatef(cam_rot.y, 0, 1, 0);
        glRotatef(cam_rot.z, 0, 0, 1);
        Physics::GetWorld()->debugDrawWorld();
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