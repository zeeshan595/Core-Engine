#ifndef _MESH_DATA
#define _MESH_DATA

class MeshData : public Module
{
public:
    void Start();
    void Stop();

    void SetMeshData(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
    void LoadOBJ(const char* filename);

    std::vector<uint32_t>       GetIndices();
    GLuint                      GetVAO();

private:
    void ComputeTangents();

    std::vector<Vertex>         vertices;
    std::vector<uint32_t>       indices;

    GLuint                      VBO             = 0;
    GLuint                      EBO             = 0;
    GLuint                      VAO             = 0;
};

#include "MeshData.cpp"
#endif