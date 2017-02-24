#ifndef _BALL_COLLIDER
#define _BALL_COLLIDER

class BallCollider : public Collider
{
public:
    BallCollider(float radius)
    {
        collider_shape = new btSphereShape(radius);
    }
};

#endif