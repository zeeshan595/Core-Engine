#ifndef _TERRAIN_COLLIDER
#define _TERRAIN_COLLIDER

class TerrainCollider : public Collider
{
public:
    struct TerrainData
    {
        float terrain_size_x;
        float terrain_size_z;
        float* heights_data;
        float max_height; 
    };

    TerrainCollider(TerrainCollider::TerrainData terrain)
    {
        collider_offset = glm::vec3(terrain.terrain_size_x / 2, terrain.max_height / 2, terrain.terrain_size_z / 2);
        collider_shape = new btHeightfieldTerrainShape(terrain.terrain_size_x, terrain.terrain_size_z, &terrain.heights_data[0], 1.0f, 0, terrain.max_height, 1, PHY_ScalarType::PHY_FLOAT, false);
    }
};

#endif