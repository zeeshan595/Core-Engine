#ifndef _RIGIDBODY
#define _RIGIDBODY

class Rigidbody : public Module
{
public:
    Rigidbody();
    void Stop();
    void Start();
    void Update();

    void SetCollisionShape(std::shared_ptr<Collider> collider);

    void SetMass(float m);
    float GetMass();

private:
    btRigidBody* body;
    btMotionState* motion;
    std::shared_ptr<Collider> collider_info;
    float mass;

    void SetupDefaultMotion();
};

#include "Rigidbody.c"

#endif