void Rigidbody::Start  ()
{
    if (collider_info != NULL)
    {
        glm::vec3 offset = collider_info->GetColliderOffset();
        glm::vec3 position = entity->transform.GetPosition() + offset;
        glm::quat rotation = entity->transform.GetRotation();

        btTransform bullet_transform;
        bullet_transform.setIdentity();
        bullet_transform.setOrigin(btVector3(position.x, position.y, position.z));
        btQuaternion rot = btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);
        bullet_transform.setRotation(rot);
        motion = new btDefaultMotionState(bullet_transform);
        
        btVector3 inertia = btVector3(0, 0, 0);
        if (mass != 0)
        {
            collider_info->GetColliderInfo()->calculateLocalInertia(mass, inertia);
        }
        btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(mass, motion, collider_info->GetColliderInfo(), inertia);
        body = new btRigidBody(info);
        body->setFriction(0.0f);
        Physics::GetWorld()->addRigidBody(body);
    }
    else
    {
        std::cout << "WARNING: no collision shape provided for rigidbody" << std::endl;
    }
}
void Rigidbody::Stop   ()
{
    if (body != NULL)
    {
        Physics::GetWorld()->removeCollisionObject(body);
        delete body;
        delete motion;
        delete collider_info;
        body            = NULL;
        motion          = NULL;
        collider_info   = NULL;
    }
}
void Rigidbody::Update ()
{
    if (mass != 0.0f)
    {
        body->activate(true);
        if (motion != NULL)
        {
            btTransform bullet_transform;
            motion->getWorldTransform(bullet_transform);
            glm::mat4x4 world_matrix;
            bullet_transform.getOpenGLMatrix(glm::value_ptr(world_matrix));
            glm::vec3 offset = collider_info->GetColliderOffset();
            world_matrix[3][0] -= offset.x;
            world_matrix[3][1] -= offset.y;
            world_matrix[3][2] -= offset.z;
            entity->transform.SetWorldMatrix(world_matrix);
        }
    }
}

void Rigidbody::ApplyForce     (glm::vec3 force)
{
    body->applyCentralForce(btVector3(force.x, force.y, force.z));
}
void Rigidbody::ApplyForce     (glm::vec3 force, glm::vec3 relative_position)
{
    body->applyForce(btVector3(force.x, force.y, force.z), btVector3(relative_position.x, relative_position.y, relative_position.z));
}
void Rigidbody::ApplyTorque    (glm::vec3 torque)
{
    body->applyTorque(btVector3(torque.x, torque.y, torque.z));
}
void Rigidbody::ClearForces    ()
{
    body->clearForces();
}

void Rigidbody::SetDamping     (float line, float angular)
{
    body->setDamping(line, angular);
}

void Rigidbody::SetAngularFactor(glm::vec3 factor)
{
    body->setAngularFactor(btVector3(factor.x, factor.y, factor.z));
}
void Rigidbody::SetVelocity        (glm::vec3 vel)
{
    body->setLinearVelocity(btVector3(vel.x, vel.y, vel.z));
}

glm::vec3       Rigidbody::GetVelocity()
{
    btVector3 vel = body->getLinearVelocity();
    return glm::vec3(vel.getX(), vel.getY(), vel.getZ());
}

void    Rigidbody::SetMass     (float m)
{
    mass = m;
}
float   Rigidbody::GetMass     ()
{
    return mass;    
}

void Rigidbody::SetCollisionShape(Collider* collider)
{
    collider_info = collider;
}