#ifndef _OBSTACLES
#define _OBSTACLES

class Obstacle : public Module
{
    public:
        Rigidbody* body = NULL;

        float gravity = 2.2f;
        float friction = 3.0f;
        float current_speed = 0.0f;

        void Start()
        {
            body = entity->GetModule<Rigidbody>();
            body->SetDamping(500.0f, 500.0f);
            body->SetAngularFactor(glm::vec3(0, 0, 0));
            
        }
        void Update()
        {
            // body->SetVelocity((-gravity * glm::vec3(0, 1, 0)) + (entity->transform.Forward() * current_speed));
        }
};

#endif