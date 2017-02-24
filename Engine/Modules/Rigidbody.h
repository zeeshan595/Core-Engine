#ifndef _RIGIDBODY
#define _RIGIDBODY

class Rigidbody : public Module
{
public:
    Rigidbody();
    ~Rigidbody();
    void Start();
    void Update();
    void SetMass(float m);
    void SetCollisionShape(Collider* collider);

private:
    btMotionState* motion;
    btRigidBody* body;
    Collider* collider_info;
    float mass;

    void SetupDefaultMotion();
};

#include "Rigidbody.c"

#endif