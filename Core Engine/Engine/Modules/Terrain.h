#ifndef _TERRAIN
#define _TERRAIN

class Terrain : public Module
{
public:
    void CreateTerrain(int size_x, int size_y, float density);

private:
    int terrain_size_x;
    int terrain_size_y;

    int GetVertexPosition(int x, int y){
        return x + ((terrain_size_x + 1) * y);
    }
};

#include "Terrain.cpp"

#endif