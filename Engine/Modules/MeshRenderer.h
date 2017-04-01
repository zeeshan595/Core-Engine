#ifndef _MESH_RENDERER
#define _MESH_RENDERER

class MeshRenderer : public Module
{
public:
    void Start();
    void Render(Camera* rendering_camera);
    
    void SetMeshData(MeshData* mesh_data);
    void SetMaterial(Material* material);
    Material* GetMaterial();

private:

    void FogShaderInfo();

    MeshData*       data                = NULL;
    Material*       material            = NULL;
};

#include "MeshRenderer.cpp"
#endif