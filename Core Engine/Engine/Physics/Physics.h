#ifndef _PHYSICS
#define _PHYSICS

class Physics
{
public:
    static void InitPhysics();
    static void DestroyPhysics();

    static btDiscreteDynamicsWorld* world;
    static btDispatcher* dispatcher;
    static btCollisionConfiguration* collision_config;
    static btBroadphaseInterface* broadphase;
    static btConstraintSolver* solver;
};
btDiscreteDynamicsWorld*        Physics::world;
btDispatcher*                   Physics::dispatcher;
btCollisionConfiguration*       Physics::collision_config;
btBroadphaseInterface*          Physics::broadphase;
btConstraintSolver*             Physics::solver;

#include "Physics.c"

#endif