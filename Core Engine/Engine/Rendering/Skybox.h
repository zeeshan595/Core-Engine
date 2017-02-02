#ifndef _SKYBOX
#define _SKYBOX

class Skybox
{
public:
    float rotation_speed = 0.05f;
    float blend_amount = 0.0f;

    Skybox();
    void Render(std::shared_ptr<Camera> camera);

    void SetTexture(std::shared_ptr<CubeTexture> tex){
        texture = tex;
    }
    void SetTexture2(std::shared_ptr<CubeTexture> tex){
        texture2 = tex;
    }
    void SetShader(std::shared_ptr<Shader> shad){
        shader = shad;
    }
    static GLuint* GetVAO(){
        return &Skybox::VAO;
    }
    static GLuint* GetVBO(){
        return &Skybox::VAO;
    }
    static GLuint* GetEBO(){
        return &Skybox::VAO;
    }

private:
    float current_rotation = 0.0f;
    std::shared_ptr<CubeTexture> texture;
    std::shared_ptr<CubeTexture> texture2;
    std::shared_ptr<Shader> shader;

    static GLuint VAO;
    static GLuint VBO;
    static GLuint EBO;
    static std::vector<glm::vec3> vertices;
    static std::vector<GLuint> indices;

    void GenerateBuffers();
};

GLuint Skybox::VAO;
GLuint Skybox::VBO;
GLuint Skybox::EBO;
std::vector<glm::vec3> Skybox::vertices;
std::vector<GLuint> Skybox::indices;

#include "Skybox.cpp"

#endif