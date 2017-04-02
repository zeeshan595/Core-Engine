#ifndef _COLLIDER
#define _COLLIDER

class Collider
{
public:
    Collider()
    {
        collider_offset = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    ~Collider()
    {
        delete collider_shape;
    }
    btCollisionShape* GetColliderInfo()
    {
        return collider_shape;
    }
    glm::vec3 GetColliderOffset()
    {
        return collider_offset;
    }

protected:
    btCollisionShape*       collider_shape;
    glm::vec3               collider_offset;
};

#endif