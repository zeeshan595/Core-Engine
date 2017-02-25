#ifndef _BOX_COLLIDER
#define _BOX_COLLIDER

class BoxCollider : public Collider
{
public:
    BoxCollider(float x_size, float y_size, float z_size)
    {
        collider_shape = new btBoxShape(btVector3(x_size, y_size, z_size));
    }
};

#endif