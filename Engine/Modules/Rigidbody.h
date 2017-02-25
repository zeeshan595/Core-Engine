#ifndef _RIGIDBODY
#define _RIGIDBODY

class Rigidbody : public Module
{
public:
    Rigidbody();
    void Stop();
    void Start();
    void Update();
    void SetMass(float m);
    void SetCollisionShape(std::shared_ptr<Collider> collider);

private:
    btRigidBody* body;
    btMotionState* motion;
    std::shared_ptr<Collider> collider_info;
    float mass;

    void SetupDefaultMotion();
};

#include "Rigidbody.c"

#endif