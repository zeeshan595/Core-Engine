btDiscreteDynamicsWorld*        Physics::world;
btDispatcher*                   Physics::dispatcher;
btCollisionConfiguration*       Physics::collision_config;
btBroadphaseInterface*          Physics::broadphase;
btConstraintSolver*             Physics::solver;


void Physics::InitPhysics()
{
    collision_config    = new btDefaultCollisionConfiguration();
    dispatcher          = new btCollisionDispatcher(collision_config);
    broadphase          = new btDbvtBroadphase();
    solver              = new btSequentialImpulseConstraintSolver();

    world               = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_config);
    world->setGravity(btVector3(0.0f, -9.82f, 0.0f));
    std::cout << "SUCCESS [Bullet Physics]" << std::endl;
}
void Physics::DestroyPhysics()
{
    delete dispatcher;
    delete collision_config;
    delete solver;
    delete broadphase;
    delete world;
}
btDiscreteDynamicsWorld* Physics::GetWorld()
{
    return world;
}