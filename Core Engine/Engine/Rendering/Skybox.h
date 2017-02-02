#ifndef _SKYBOX
#define _SKYBOX

class Skybox
{
public:
    std::shared_ptr<CubeTexture> texture;

    Skybox()
    {
        texture = std::shared_ptr<CubeTexture>(new CubeTexture("right.png", "left.png", "top.png", "bottom.png", "front.png", "back.png"));
        if (Skybox::shader == nullptr)
            GenerateBuffers();
    }
    ~Skybox()
    {
        glDeleteBuffers(1, &Skybox::EBO);
        glDeleteBuffers(1, &Skybox::VBO);
        glDeleteVertexArrays(1, &Skybox::VAO);
    }
    void Render(std::shared_ptr<Camera> camera)
    {
        glUseProgram(Skybox::shader->GetShaderProgram());

        GLint projection_uniform = glGetUniformLocation(Skybox::shader->GetShaderProgram(), "projection_matrix");
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));

        glm::mat4x4 view_mat = camera->GetViewMatrix();
        view_mat[3][0] = 0;
        view_mat[3][1] = 0;
        view_mat[3][2] = 0;
        GLint view_uniform = glGetUniformLocation(Skybox::shader->GetShaderProgram(), "view_matrix");
        glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view_mat));

        if (texture != nullptr)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, texture->GetTextureMap());
            GLint texture_uniform = glGetUniformLocation(Skybox::shader->GetShaderProgram(), "cube_map");
            glUniform1i(texture_uniform, 0);
        }

        glBindVertexArray(Skybox::VAO);
        glDrawElements(GL_TRIANGLES, Skybox::indices.size(), GL_UNSIGNED_INT, 0);
    }
private:
    static std::shared_ptr<Shader> shader;
    static GLuint VAO;
    static GLuint VBO;
    static GLuint EBO;
    static std::vector<glm::vec3> vertices;
    static std::vector<GLuint> indices;

    void GenerateBuffers()
    {
        Skybox::shader = std::shared_ptr<Shader>(new Shader("skyboxVS.glsl", "skyboxFS.glsl"));
        vertices.resize(Cube::vertices.size());
        for (int i = 0; i < Cube::vertices.size(); i++)
            vertices[i] = Cube::vertices[i].position * 500.0f;
        indices = Cube::indices;
        //Create VAO
        glGenVertexArrays(1, &Skybox::VAO);
        glBindVertexArray(Skybox::VAO);
        //Create VBO
        glGenBuffers(1, &Skybox::VBO);
        glBindBuffer(GL_ARRAY_BUFFER, Skybox::VBO);
        glBufferData(GL_ARRAY_BUFFER, Skybox::vertices.size() * sizeof(glm::vec3), &Skybox::vertices[0], GL_STATIC_DRAW);
        //Create EBO
        glGenBuffers(1, &Skybox::EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Skybox::EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Skybox::indices.size() * sizeof(GLuint), &Skybox::indices[0], GL_STATIC_DRAW);
        
        //Shader Info
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
    }
};

std::shared_ptr<Shader> Skybox::shader;
GLuint Skybox::VAO;
GLuint Skybox::VBO;
GLuint Skybox::EBO;
std::vector<glm::vec3> Skybox::vertices;
std::vector<GLuint> Skybox::indices;

#endif