#ifndef _BOX_COLLIDER
#define _BOX_COLLIDER

class BoxCollider : public Collider
{
public:
    BoxCollider(glm::vec3 size)
    {
        collider_shape = new btBoxShape(btVector3(size.x, size.y, size.z));
    }
};

#endif