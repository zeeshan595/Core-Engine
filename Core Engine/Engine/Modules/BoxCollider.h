#ifndef _BOX_COLLIDER
#define _BOX_COLLIDER

class BoxCollider : public Module
{
public:
    btRigidBody* body;
    float mass = 1.0f;

    void Start(){
        btTransform bullet_transform;
        bullet_transform.setIdentity();
        bullet_transform.setOrigin(btVector3(attached_to->transform.position.x, attached_to->transform.position.y, attached_to->transform.position.z));
        btBoxShape* cube = new btBoxShape(btVector3(attached_to->transform.scale.x, attached_to->transform.scale.y, attached_to->transform.scale.z));
        btMotionState* motion = new btDefaultMotionState(bullet_transform);
        btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(mass, motion, cube);
        body = new btRigidBody(info);
        Physics::world->addRigidBody(body);
    }

    void Update(){
        btVector3 centre_pos = body->getCenterOfMassPosition();
        attached_to->transform.position = glm::vec3(centre_pos.getX(), centre_pos.getY(), centre_pos.getZ());
    }
};

#endif