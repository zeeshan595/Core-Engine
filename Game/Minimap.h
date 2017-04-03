#ifndef _MINIMAP
#define _MINIMAP

class Minimap : public Module
{
public:
    Entity* player_car          = NULL;
    float   camera_height       = 30.0f;

    void Start()
    {
        player_car = Environment::FindEntity("Car");
    }

    void Update()
    {
        glm::vec3 offset = player_car->transform.GetPosition() + glm::vec3(0, camera_height, 0);
        entity->transform.SetPosition(LerpPosition(entity->transform.GetPosition(), offset, Time::delta_time * 5.0f));
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