#ifndef _MESH
#define _MESH

class Mesh : public Module
{
public:
    ~Mesh();

    void Render(std::shared_ptr<Camera> camera);

    void LoadOBJFile(std::string filename);
    void LoadDefaultCube();
    void LoadDefaultPlane();
    void CreateMesh(std::vector<Vertex> verts, std::vector<GLuint> ind);

    void ApplySurface(std::shared_ptr<Surface> surface);
    std::shared_ptr<Surface> GetSurface();

private:
    std::shared_ptr<Surface> surface;
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    void GenerateBuffers();
};

#include "Mesh.c"

#endif