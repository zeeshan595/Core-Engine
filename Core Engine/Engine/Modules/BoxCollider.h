#ifndef _BOX_COLLIDER
#define _BOX_COLLIDER

class BoxCollider : public Module
{
public:
    void Start(){
        btTransform bullet_transform;
        bullet_transform.setIdentity();
        float x = attached_to->transform.position.x;
        float y = attached_to->transform.position.y;
        float z = attached_to->transform.position.z;
        bullet_transform.setOrigin(x, y, z);
        btCubeShape* cube = new btCubeShape();
    }
};

#endif