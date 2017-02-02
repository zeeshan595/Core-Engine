#ifndef _UI_MESH
#define _UI_MESH

class UIMesh : public Module
{
public:
    glm::vec4 rect;
    float rotation;

    UIMesh(){
        texture = std::shared_ptr<Texture>(new Texture("texture.png"));
        rect = glm::vec4(0, 0, 200, 200);
        rotation = 0;
        if (UIMesh::shader == nullptr)        
            GenerateBuffers();
    }
    ~UIMesh(){
        glDeleteBuffers(1, &UIMesh::EBO);
        glDeleteBuffers(1, &UIMesh::VBO);
        glDeleteVertexArrays(1, &UIMesh::VAO);
    }
    void Render(std::shared_ptr<Camera> camera, std::vector<std::shared_ptr<Light>>* lights){

        glUseProgram(UIMesh::shader->GetShaderProgram());

        //ui_position
        GLint ui_position_uniform = glGetUniformLocation(UIMesh::shader->GetShaderProgram(), "ui_transformation");
        glUniformMatrix4fv(ui_position_uniform, 1, GL_FALSE, glm::value_ptr(GetTransformationMatrix()));

        //Textures
        if (texture != nullptr)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->GetTextureMap());
            GLint texture_uniform = glGetUniformLocation(UIMesh::shader->GetShaderProgram(), "ui_texture_map");
            glUniform1i(texture_uniform, 0);
        }

        glBindVertexArray(UIMesh::VAO);
        glDrawElements(GL_TRIANGLES, UIMesh::indices.size(), GL_UNSIGNED_INT, 0);
    }

private:
    std::shared_ptr<Texture> texture;

    static std::shared_ptr<Shader> shader;
    static GLuint VAO;
    static GLuint VBO;
    static GLuint EBO;
    static std::vector<glm::vec2> vertices;
    static std::vector<int> indices;

    static void GenerateBuffers(){
        UIMesh::vertices  = {
            {  0,  1 },
            {  0,  0 },
            {  1,  1 },
            {  1,  0 }
        };
        UIMesh::indices = {
            0, 1, 2,
            1, 3, 2
        };
        UIMesh::shader = std::shared_ptr<Shader>(new Shader("uiVS.glsl","uiFS.glsl"));
        //Create VAO
        glGenVertexArrays(1, &UIMesh::VAO);
        glBindVertexArray(UIMesh::VAO);
        //Create VBO
        glGenBuffers(1, &UIMesh::VBO);
        glBindBuffer(GL_ARRAY_BUFFER, UIMesh::VBO);
        glBufferData(GL_ARRAY_BUFFER, UIMesh::vertices.size() * sizeof(glm::vec2), &UIMesh::vertices[0], GL_STATIC_DRAW);
        //Create EBO
        glGenBuffers(1, &UIMesh::EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UIMesh::EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, UIMesh::indices.size() * sizeof(GLuint), &UIMesh::indices[0], GL_STATIC_DRAW);
        
        //Shader Info
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
    }

    glm::mat4x4 GetTransformationMatrix(){
        glm::vec4 mapped_rect = rect;
        mapped_rect = glm::vec4(mapped_rect.x / Screen::width, mapped_rect.y / Screen::height, mapped_rect.z / Screen::width, mapped_rect.w  / Screen::height);

        glm::mat4x4 model_matrix = glm::mat4x4(1.0f);
        model_matrix = glm::translate(model_matrix, glm::vec3(mapped_rect.x, mapped_rect.y, 0.0f));
        model_matrix = glm::rotate(model_matrix, rotation, glm::vec3(0, 0, 1.0f));
        model_matrix = glm::scale(model_matrix, glm::vec3(mapped_rect.z, mapped_rect.w, 0.0f));
        return model_matrix;
    }
};

std::shared_ptr<Shader> UIMesh::shader;
GLuint UIMesh::VAO;
GLuint UIMesh::VBO;
GLuint UIMesh::EBO;
std::vector<glm::vec2> UIMesh::vertices;
std::vector<int> UIMesh::indices;

#endif