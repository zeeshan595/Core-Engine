#ifndef _RIGIDBODY
#define _RIGIDBODY

class Rigidbody : public Module
{
public:
    void Start  ();
    void Stop   ();
    void Update ();

    void ApplyForce         (glm::vec3 force);
    void ApplyForce         (glm::vec3 force, glm::vec3 relative_position);
    void ApplyTorque        (glm::vec3 torque);
    void ClearForces        ();

    void SetDamping         (float line, float angular);
    void SetAngularFactor   (glm::vec3 factor);
    void SetVelocity        (glm::vec3 vel);

    glm::vec3       GetVelocity();

    void    SetMass     (float m);
    float   GetMass     ();

    void SetCollisionShape(Collider* collider);

private:
    btRigidBody*        body            = NULL;
    btMotionState*      motion          = NULL;
    Collider*           collider_info   = NULL;
    float               mass            = 1.0f;

};

#include "Rigidbody.cpp"
#endif