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
    std::string spec_map;
    std::vector<std::string> tile_textures;
    std::shared_ptr<Shader> terrain_shader;

    Terrain();
    void CreateTerrain();
    float TerrainHeight(float world_x, float world_z);

private:
    const int MAX_PIXEL_COLOUR = 256 * 256 * 256;
    SDL_Surface* height_map_surface;
    std::vector<std::vector<float> > heights;

    glm::vec3 CalculateNormal(int x, int z);
    float GetPixelColor(int x, int y);
    Uint32 GetPixel(int xFloat, int yFloat);
    int GetVertexPosition(int x, int y){
        return x + ((terrain_size_x + 1) * y);
    }
    float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
        float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
        float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
        float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
        float l3 = 1.0f - l1 - l2;
        return l1 * p1.y + l2 * p2.y + l3 * p3.y;
    }
};

#include "Terrain.c"

#endif