#ifndef _GIZMO
#define _GIZMO

class Gizmo : public Module
{
public:
    Gizmo();
    ~Gizmo();

    void Render(std::shared_ptr<Camera> camera);
    void SetTexture(std::shared_ptr<Texture> tex){
        texture = tex;
    }
    
private:
    std::shared_ptr<Texture> texture;

    static std::shared_ptr<Shader> shader;
    static std::vector<Vertex> vertices;
    static std::vector<GLuint> indices;
    static GLuint VBO;
    static GLuint EBO;
    static GLuint VAO;
    static int gizmos_amount;

    void GenerateBuffers();
};

GLuint                      Gizmo::VBO;
GLuint                      Gizmo::EBO;
GLuint                      Gizmo::VAO;
int                         Gizmo::gizmos_amount;
std::shared_ptr<Shader>    Gizmo::shader;
std::vector<Vertex>         Gizmo::vertices;
std::vector<GLuint>         Gizmo::indices;


#include "Gizmo.c"

#endif