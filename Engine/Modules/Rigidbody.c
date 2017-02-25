Rigidbody::Rigidbody()
{
    mass = 1.0f;
    body = nullptr;
    motion = nullptr;
    collider_info = nullptr;
}

void Rigidbody::Stop()
{
    Physics::GetWorld()->removeCollisionObject(body);
    delete body;
    delete motion;
}

void Rigidbody::Start()
{
    if (collider_info != nullptr)
    {
        glm::vec3 offset = collider_info->GetColliderOffset();
        glm::vec3 position = attached_to->transform.GetPosition() + offset;
        glm::quat rotation = attached_to->transform.GetRotation();

        btTransform bullet_transform;
        bullet_transform.setIdentity();
        bullet_transform.setOrigin(btVector3(position.x, position.y, position.z));
        btQuaternion rot = btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w);
        bullet_transform.setRotation(rot);
        motion = new btDefaultMotionState(bullet_transform);
        
        btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(mass, motion, collider_info->GetColliderInfo());
        body = new btRigidBody(info);
        Physics::GetWorld()->addRigidBody(body);
    }
    else
        std::cout << "WARNING: no collision shape provided for rigidbody" << std::endl;
}

void Rigidbody::Update()
{
    if (mass != 0.0f)
    {
        if (motion != nullptr)
        {
            btTransform bullet_transform;
            motion->getWorldTransform(bullet_transform);
            glm::mat4x4 world_matrix;
            bullet_transform.getOpenGLMatrix(glm::value_ptr(world_matrix));
            
            attached_to->transform.Translate(glm::vec3(world_matrix[3][0], world_matrix[3][1], world_matrix[3][2]));
            attached_to->transform.SetRotation(glm::toQuat(world_matrix));
        }
    }
}

void Rigidbody::ApplyForce(glm::vec3 force)
{
    body->applyCentralForce(btVector3(force.x, force.y, force.z));
}
void Rigidbody::ApplyForce(glm::vec3 force, glm::vec3 relative_position)
{
    body->applyForce(btVector3(force.x, force.y, force.z), btVector3(relative_position.x, relative_position.y, relative_position.z));
}
void Rigidbody::ApplyTorque(glm::vec3 torque)
{
    body->applyTorque(btVector3(torque.x, torque.y, torque.z));
}
void Rigidbody::ClearForces()
{
    body->clearForces();
}
void Rigidbody::SetDamping(float line, float angular)
{
    body->setDamping(line, angular);
}

void Rigidbody::SetMass(float m)
{
    mass = m;
}
float Rigidbody::GetMass()
{
    return mass;
}

void Rigidbody::SetCollisionShape(std::shared_ptr<Collider> collider)
{ 
    collider_info = collider;
}