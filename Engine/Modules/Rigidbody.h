#ifndef _RIGIDBODY
#define _RIGIDBODY

class Rigidbody : public Module
{
public:
    Rigidbody();
    void Stop();
    void Start();
    void Update();

    void ApplyForce(glm::vec3 force);
    void ApplyForce(glm::vec3 force, glm::vec3 relative_position);
    void ApplyTorque(glm::vec3 torque);
    void ClearForces();
    void SetDamping(float line, float angular);

    void SetMass(float m);
    float GetMass();

    void SetCollisionShape(std::shared_ptr<Collider> collider);

private:
    btRigidBody* body;
    btMotionState* motion;
    std::shared_ptr<Collider> collider_info;
    float mass;
};

#include "Rigidbody.c"

#endif