#ifndef _TERRAIN_COLLIDER
#define _TERRAIN_COLLIDER

class TerrainCollider : public Module
{
public:
    btRigidBody* body;
    btHeightfieldTerrainShape* terrain_collider;
    btMotionState* motion;
    std::shared_ptr<Terrain> terrain;

    void Start(){
        terrain = attached_to->GetModule<Terrain>();
        if (terrain == nullptr)
        {
            std::cout << "TerrainCollider could not find Terrain module" << std::endl;
            return;
        }
        btTransform bullet_transform;
        bullet_transform.setIdentity();
        bullet_transform.setOrigin(btVector3(attached_to->transform.position.x + (terrain->terrain_size_x / 2), attached_to->transform.position.y + (terrain->max_height / 2), attached_to->transform.position.z + (terrain->terrain_size_z / 2)));
        btQuaternion rot = btQuaternion(attached_to->transform.rotation.x, attached_to->transform.rotation.y, attached_to->transform.rotation.z, attached_to->transform.rotation.w);
        bullet_transform.setRotation(rot);

        float* hightfield_data = new float[terrain->terrain_size_x * terrain->terrain_size_z];
        for (int i = 0; i < terrain->terrain_size_z; i++){
            for (int j = 0; j < terrain->terrain_size_x; j++){
                hightfield_data[(i * terrain->terrain_size_x) + j] = terrain->TerrainHeight(j + attached_to->transform.position.x, i + attached_to->transform.position.z);
            }
        }
        terrain_collider = new btHeightfieldTerrainShape(terrain->terrain_size_x, terrain->terrain_size_z, &hightfield_data[0], 1.0f, 0, terrain->max_height, 1, PHY_ScalarType::PHY_FLOAT, false);
        motion = new btDefaultMotionState(bullet_transform);
        btRigidBody::btRigidBodyConstructionInfo info = btRigidBody::btRigidBodyConstructionInfo(0, motion, terrain_collider);
        body = new btRigidBody(info);
        Physics::world->addRigidBody(body);
    }

    void Stop(){
        Physics::world->removeCollisionObject(body);
        delete body;
        delete terrain_collider;
        delete motion;
    }
};

#endif