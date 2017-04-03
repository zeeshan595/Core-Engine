#ifndef _PHYSICS
#define _PHYSICS

class Physics
{
public:
    static void InitPhysics();
    static void DestroyPhysics();
    static btDiscreteDynamicsWorld* GetWorld();

private:
    static btDiscreteDynamicsWorld*     world;
    static btDispatcher*                dispatcher;
    static btCollisionConfiguration*    collision_config;
    static btBroadphaseInterface*       broadphase;
    static btConstraintSolver*          solver;
    static GLDebugDrawer*               debug_drawer;
    
};

#include "Physics.cpp"
#endif