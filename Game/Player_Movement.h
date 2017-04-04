#ifndef _PLAYER_MOVMENT
#define _PLAYER_MOVMENT

class PlayerMovement : public Module
{
    public:
        Rigidbody*      body                = NULL;
        AudioSource*    audio               = NULL;
        float           speed               = 7.0f;
        float           turn_speed          = 30.0f;
        float           gravity             = 2.2f;

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
                    speed+= Time::delta_time; 
                    body->SetVelocity((-gravity * glm::vec3(0, 1, 0)) + (entity->transform.Forward() * speed));
            }
            else if (Input::GetKey(SDLK_DOWN))
            {
                    speed-= Time::delta_time; 
                    body->SetVelocity((-gravity * glm::vec3(0, 1, 0)) + (entity->transform.Forward() * -speed));
            }
         
            if (Input::GetKey(SDLK_RIGHT))
            {
                body->ApplyTorque(glm::vec3(0, -turn_speed, 0));
            }
            else if (Input::GetKey(SDLK_LEFT))
            {
                body->ApplyTorque(glm::vec3(0, turn_speed, 0));
            }

            glm::vec3 current_pos = entity->transform.GetPosition();
            if (current_pos.x > 80 && current_pos.x < 88 && current_pos.z > 75)
            {
                Environment::SetEnvironment((int32_t)2, true);
                entity->transform.SetPosition(glm::vec3(84, 2, 10));
                entity->transform.Rotate(glm::vec3(0, -1.5f, 0));
            }
        }

};

#endif