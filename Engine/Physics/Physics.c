void Physics::InitPhysics()
{
    Physics::collision_config = new btDefaultCollisionConfiguration();
    Physics::dispatcher = new btCollisionDispatcher(Physics::collision_config);
    Physics::broadphase = new btDbvtBroadphase();
    Physics::solver = new btSequentialImpulseConstraintSolver();

    Physics::world = new btDiscreteDynamicsWorld(Physics::dispatcher, Physics::broadphase, Physics::solver, Physics::collision_config);
    Physics::world->setGravity(btVector3(0.0f, -9.82f, 0.0f));
}

void Physics::DestroyPhysics()
{
    delete Physics::dispatcher;
    delete Physics::collision_config;
    delete Physics::solver;
    delete Physics::broadphase;
    delete Physics::world;
}