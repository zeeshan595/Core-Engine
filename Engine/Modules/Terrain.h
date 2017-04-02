#ifndef _TERRAIN
#define _TERRAIN

class Terrain : public Module
{
public:
    void Start();

    void SetMaxHeight               (float max_height);
    void SetTerrainSize             (uint32_t x, uint32_t z);
    void SetDensity                 (float density);
    void SetHeightMapTexture        (const char* hight_map);

    float           GetMaxHeight    ();
    void            GetTerrainSize  (uint32_t &x, uint32_t &z);
    float           GetDensity      ();
    const char*     GetHeightMap    ();

private:

    TerrainCollider::TerrainData     GetTerrainCollisionData ();

    SDL_Surface*    GetHeightMapImage   ();
    glm::vec3       ComputeNormal       (uint32_t x, uint32_t z, SDL_Surface* height_map_surface);
    float           GetHeightFromPixel  (uint32_t x, uint32_t z, SDL_Surface* height_map_surface);
    uint32_t        GetPixelFromArray   (uint32_t x, uint32_t z, SDL_Surface* height_map_surface);
    uint32_t        GetVertexPosition   (uint32_t x, uint32_t z);

    const uint32_t                      MAX_PIXEL_COLOR         = 256 * 256 * 256;
    float                               max_height              = 10.0f;
    uint32_t                            terrain_size_x          = 100;
    uint32_t                            terrain_size_z          = 100;
    float                               density                 = 1.0f;
    const char*                         height_map              = "height_map.png";
    std::vector<std::vector<float> >    heights;
};

#include "Terrain.cpp"
#endif