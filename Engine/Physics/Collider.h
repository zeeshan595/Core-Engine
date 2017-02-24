#ifndef _COLLIDER
#define _COLLIDER

class Collider
{
public:
    btCollisionShape* GetColliderInfo()
    {
        return collider_shape;
    }
    glm::vec3 GetColliderOffset()
    {
        return collider_offset;
    }
    Collider()
    {
        collider_offset = glm::vec3(0.0f, 0.0f, 0.0f);
    }
    ~Collider()
    {
        delete collider_shape;
    }

protected:
    btCollisionShape* collider_shape;
    glm::vec3 collider_offset;
};

#endif