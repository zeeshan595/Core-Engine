btDiscreteDynamicsWorld*        Physics::world                  = NULL;
btDispatcher*                   Physics::dispatcher             = NULL;
btCollisionConfiguration*       Physics::collision_config       = NULL;
btBroadphaseInterface*          Physics::broadphase             = NULL;
btConstraintSolver*             Physics::solver                 = NULL;
GLDebugDrawer*                  Physics::debug_drawer           = NULL;


void Physics::InitPhysics()
{
    collision_config    = new btDefaultCollisionConfiguration();
    dispatcher          = new btCollisionDispatcher(collision_config);
    broadphase          = new btDbvtBroadphase();
    solver              = new btSequentialImpulseConstraintSolver();

    world               = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_config);
    debug_drawer        = new GLDebugDrawer();
    debug_drawer->setDebugMode(btIDebugDraw::DebugDrawModes::DBG_DrawWireframe);
    world->setDebugDrawer(debug_drawer);
    world->setGravity(btVector3(0.0f, -9.82f, 0.0f));
    std::cout << "SUCCESS [Bullet Physics]" << std::endl;
}
void Physics::DestroyPhysics()
{
    delete debug_drawer;
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