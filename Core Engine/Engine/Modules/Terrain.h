#ifndef _TERRAIN
#define _TERRAIN

class Terrain : public Module
{
public:
    float max_height;
    int terrain_size_x;
    int terrain_size_y;
    float density;
    std::string blend_map;
    std::string height_map;
    std::string spec_map;
    std::vector<std::string> tile_textures;
    std::shared_ptr<Shader> terrain_shader;

    Terrain();
    void CreateTerrain();

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
};

#include "Terrain.cpp"

#endif