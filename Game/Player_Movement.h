#ifndef _PLAYER_MOVMENT
#define _PLAYER_MOVMENT

class PlayerMovement : public Module
{
    public:
        Rigidbody*      body                = NULL;
        AudioSource*    audio               = NULL;
        float           acceleration        = 5.0f;
        float           max_speed           = 7.0f;
        float           reverse_accel       = 10.0f;
        float           reverse_speed       = 5.0f;
        float           turn_speed          = 30.0f;
        float           gravity             = 2.2f;
        float           friction            = 3.0f;

        float           current_speed       = 0.0f;

        void Start()
        {
            body    = entity->GetModule<Rigidbody>();
            audio   = entity->GetModule<AudioSource>();
            body->SetDamping(0.5f, 2.0f);
            body->SetAngularFactor(glm::vec3(0, 1, 0));
            
        }
         void Update()
        {
            if (Input::GetKey(SDLK_UP))
            {
                if (current_speed < max_speed)
                    current_speed += Time::delta_time * acceleration  * (1.0f / glm::abs(glm::length(body->GetVelocity())));
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
            audio->SetPitch((current_speed / max_speed) + 0.3f);

            glm::vec3 current_pos = entity->transform.GetPosition();
            if (current_pos.x > 80 && current_pos.x < 88 && current_pos.z > 75)
            {
                Environment::SetEnvironment((int32_t)2, true);
                entity->transform.SetPosition(glm::vec3(84, 2, 10));
                entity->transform.Rotate(glm::vec3(0, -1.57f, 0));
            }
        }

};

#endif