#ifndef _BOX_COLLIDER
#define _BOX_COLLIDER

class BoxCollider : public Module
{
public:
    btRigidBody* body;
    btBoxShape* cube;
    btMotionState* motion;
    float mass = 1.0f;

    void Start(){
        btTransform bullet_transform;
        bullet_transform.setIdentity();
        bullet_transform.setOrigin(btVector3(attached_to->transform.position.x, attached_to->transform.position.y, attached_to->transform.position.z));
        btQuaternion rot = btQuaternion::getIdentity();
        bullet_transform.setRotation(rot);
        cube = new btBoxShape(btVector3(attached_to->transform.scale.x, attached_to->transform.scale.y, attached_to->transform.scale.z));
        btVector3 inertia = btVector3(0, 0, 0);
        if (mass != 0)
            cube->calculateLocalInertia(mass, inertia);
        motion = new btDefaultMotionState(bullet_transform);
        btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(mass, motion, cube, inertia);
        body = new btRigidBody(info);
        Physics::world->addRigidBody(body);
    }

    void Stop(){
        Physics::world->removeCollisionObject(body);
        delete body;
        delete cube;
        delete motion;
    }

    void Update(){
        btTransform bullet_transform; 
        motion->getWorldTransform(bullet_transform);
        btVector3 centre_pos = bullet_transform.getOrigin();
        btVector3 rotation = bullet_transform.getRotation().getAxis();
        float w = bullet_transform.getRotation().getW();
        attached_to->transform.position = glm::vec3(centre_pos.getX(), centre_pos.getY(), centre_pos.getZ());
        float rotation_x = Transform::ToDegrees(glm::asin(rotation.getX()) * glm::acos(w));
        float rotation_y = Transform::ToDegrees(glm::asin(rotation.getY()) * glm::acos(w));
        float rotation_z = Transform::ToDegrees(glm::asin(rotation.getZ()) * glm::acos(w));
        attached_to->transform.rotation = glm::vec3(rotation_x, rotation_y, rotation_z);
    }
};

#endif