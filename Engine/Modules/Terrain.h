#ifndef _TERRAIN
#define _TERRAIN

class Terrain : public Module
{
public:
    float max_height;
    int terrain_size_x;
    int terrain_size_z;
    float density;
    std::string blend_map;
    std::string height_map;

    std::string tile_texture0;
    std::string tile_texture1;
    std::string tile_texture2;
    std::string tile_texture3;

    std::shared_ptr<Shader> terrain_shader;

    Terrain();
    void CreateTerrain();
    float TerrainHeight(float world_x, float world_z);
    TerrainCollider::TerrainData GetTerrainCollisionInfo();

private:
    const int MAX_PIXEL_COLOUR = 256 * 256 * 256;
    SDL_Surface* height_map_surface;
    std::vector<std::vector<float> > heights;

    float* GetHeightsData();
    glm::vec3 CalculateNormal(int x, int z);
    float GetPixelColor(int x, int y);
    Uint32 GetPixel(int xFloat, int yFloat);
    int GetVertexPosition(int x, int y);
    float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
};

#include "Terrain.c"

#endif