#ifndef _UI
#define _UI

class UI : public Module
{
public:
    void Start();
    void Stop();
    void Render(Camera* rendering_camera);

    void SetTexture(Texture* t);
    Texture*    GetTexture();

    void SetShader(Shader* s);
    Shader*     GetShader();

private:
    GLuint                  VAO             = 0;
    GLuint                  VBO             = 0;
    GLuint                  EBO             = 0;
    Shader*                 shader          = NULL;
    Texture*                texture         = NULL;
    std::vector<glm::vec3>  vertices;
    std::vector<uint32_t>   indices;
};

#include "UI.cpp"
#endif