#ifndef _CAR_MOVMENT
#define _CAR_MOVMENT

class CarMovment : public Module
{
public:
    Rigidbody*  body                = NULL;
    float       acceleration        = 5.0f;
    float       max_speed           = 20.0f;
    float       reverse_accel       = 10.0f;
    float       reverse_speed       = 5.0f;
    float       turn_speed          = 5.0f;
    float       gravity             = 5.2f;
    float       friction            = 3.0f;

    float       current_speed       = 0.0f;

    void Start()
    {
        body = entity->GetModule<Rigidbody>();
        body->SetDamping(0.5f, 2.0f);
        body->SetAngularFactor(glm::vec3(0, 1, 0));
    }

    void Update()
    {
        if (Input::GetKey(SDLK_UP))
        {
            if (current_speed < max_speed)
                current_speed += Time::delta_time * acceleration  * (1.0f / glm::abs(current_speed));
        }
        else if (Input::GetKey(SDLK_DOWN))
        {
            if (current_speed > -reverse_speed)
                current_speed -= Time::delta_time * reverse_accel;
        }
        else
        {
            if (current_speed <= 0)
                current_speed += Time::delta_time * friction;
            else if (current_speed > 0)
                current_speed -= Time::delta_time * friction;
        }
        if (Input::GetKey(SDLK_RIGHT))
        {
            body->ApplyTorque(glm::vec3(0, -turn_speed, 0));
        }
        else if (Input::GetKey(SDLK_LEFT))
        {
            body->ApplyTorque(glm::vec3(0, turn_speed, 0));
        }

        body->SetVelocity((-gravity * glm::vec3(0, 1, 0)) + (entity->transform.Forward() * current_speed));
    }
};

#endif