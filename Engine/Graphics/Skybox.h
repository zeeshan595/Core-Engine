#ifndef _SKYBOX
#define _SKYBOX

class Skybox
{
public:
    Skybox(CubeTexture* cube_texture, Shader* shader);
    ~Skybox();

    void Start();
    void Stop();
    void Render(Camera* camera);

    void SetTexture (CubeTexture* texture);
    void SetShader  (Shader* shader);

private:
    void GenerateBuffers();

    GLuint                      VAO         = 0;
    GLuint                      VBO         = 0;
    GLuint                      EBO         = 0;
    std::vector<glm::vec3>      vertices;
    std::vector<GLuint>         indices;
    CubeTexture*                texture     = NULL;
    Shader*                     shader      = NULL;
};

#include "Skybox.cpp"
#endif