#ifndef _CAR_MOVMENT
#define _CAR_MOVMENT

class CarMovment : public Module
{
public:
    Rigidbody*  body                = NULL;
    float       acceleration        = 15.0f;
    float       max_speed           = 20.0f;
    float       reverse_accel       = 12.0f;
    float       reverse_speed       = 10.0f;
    float       break_force         = 1.0f;
    float       turn_speed          = 5.0f;

    void Start()
    {
        body = entity->GetModule<Rigidbody>();
    }

    void Update()
    {
        if (Input::GetKey(SDLK_UP))
        {
            if (glm::length(body->GetVelocity()) < max_speed)
                body->ApplyForce(entity->transform.Forward() * acceleration);
        }
        else if (Input::GetKey(SDLK_DOWN))
        {
            if (glm::length(body->GetVelocity()) < reverse_speed)
                body->ApplyForce(entity->transform.Forward() * -reverse_accel);
            else
                body->ApplyForce(-body->GetVelocity() * break_force);
        }
        if (Input::GetKey(SDLK_RIGHT))
        {
            body->ApplyTorque(glm::vec3(0, -turn_speed, 0));
        }
        else if (Input::GetKey(SDLK_LEFT))
        {
            body->ApplyTorque(glm::vec3(0, turn_speed, 0));
        }
    }
};

#endif