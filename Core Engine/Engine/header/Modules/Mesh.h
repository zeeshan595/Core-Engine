#ifndef _MESH
#define _MESH

#include "Module.h"
#include "../Surface.h"
#include "../OBJLoader.h"

class Mesh : public Module
{
  public:
    Mesh()
    {
        LoadDefaultCube();
        GenerateBuffers();
    }
    ~Mesh()
    {
        glDeleteBuffers(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
    void ApplySurface(std::shared_ptr<Surface> s)
    {
        surface = s;
    }

    void LoadModel(const std::string filename)
    {
        IndexedModel model = OBJModel(MODEL_PATH + filename).ToIndexedModel();
        if (model.positions.size() == model.texCoords.size() && model.texCoords.size() == model.normals.size())
        {
            const int VERTS_LEN = model.positions.size();
            const int INDICES_LEN = model.indices.size();
            verts.resize(VERTS_LEN);
            indices.resize(INDICES_LEN);

            for (int i = 0; i < VERTS_LEN; i++)
            {
                verts[i] = {
                    model.positions[i], model.texCoords[i], model.normals[i]};
            }

            for (int i = 0; i < INDICES_LEN; i++)
            {
                indices[i] = model.indices[i];
            }

            GenerateBuffers();
        }
        else
        {
            std::cout << "WARNING: model vertices, uv and normals do not match " << filename << std::endl;
        }
    }

    void Render(std::shared_ptr<Camera> camera)
    {
        if (keys_pressed[SDLK_RIGHT])
        {
            attached_to->transform.rotation += glm::vec3(0, 50, 0) * delta_time;
        }
        if (keys_pressed[SDLK_UP])
        {
            attached_to->transform.rotation += glm::vec3(50, 0, 0) * delta_time;
        }

        if (surface != nullptr)
        {
            glUseProgram(surface->GetShaderProgram());
            //Transform
            GLint mvp_uniform = glGetUniformLocation(surface->GetShaderProgram(), "MVP");
            glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix() * camera->GetViewMatrix() * attached_to->transform.GetWorldMatrix()));
            //Texture
            
            if (surface->GetTexture() != nullptr)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, surface->GetTexture()->GetTextureMap());
                GLint texture_uniform = glGetUniformLocation(surface->GetShaderProgram(), "texture0");
                glUniform1i(texture_uniform, 0);
            }
            

            glm::vec3 light_position = glm::vec3(0.0f, 1.0f, 5.0f);
            GLint light_position_uniform = glGetUniformLocation(surface->GetShaderProgram(), "lightPosition");
            glUniform3fv(light_position_uniform, 1, &light_position[0]);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        }
        else
        {
            std::cout << "WARNING: surface is null asigning simpleVS & simpleFS" << std::endl;
            surface = std::shared_ptr<Surface>(new Surface("simpleVS.glsl", "simpleFS.glsl"));
        }
    }

  private:
    std::vector<Vertex> verts;
    std::vector<GLuint> indices;
    std::shared_ptr<Surface> surface = nullptr;
    GLuint VBO = 0;
    GLuint EBO = 0;
    GLuint VAO = 0;

    void GenerateBuffers()
    {
        if (VAO != 0)
        {
            glDeleteBuffers(1, &EBO);
            glDeleteBuffers(1, &VBO);
            glDeleteVertexArrays(1, &VAO);
            VBO = 0;
            EBO = 0;
            VAO = 0;
        }

        //Create VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        //Create VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), &verts[0], GL_STATIC_DRAW);
        //Create EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
        
        //Shader Info
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texture));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    }

    void LoadDefaultCube()
    {
        verts = {
            //Front
            {glm::vec3(-1.0f, 1.0f, 1.0f),
             glm::vec2(0.0f, 0.0f), glm::vec3(-0.3f, 0.3f, 0.3f)}, // Top Left

            {glm::vec3(-1.0f, -1.0f, 1.0f),
             glm::vec2(0.0f, 1.0f), glm::vec3(-0.3f, -0.3f, 0.3f)}, // Bottom Left

            {glm::vec3(1.0f, -1.0f, 1.0f),
             glm::vec2(1.0f, 1.0f), glm::vec3(0.3f, -0.3f, 0.3f)}, //Bottom Right

            {glm::vec3(1.0f, 1.0f, 1.0f),
             glm::vec2(1.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f)}, // Top Right

            //back
            {glm::vec3(-1.0f, 1.0f, -1.0f),
             glm::vec2(0.0f, 0.0f), glm::vec3(-0.3f, 0.3f, -0.3f)}, // Top Left

            {glm::vec3(-1.0f, -1.0f, -1.0f),
             glm::vec2(0.0f, 1.0f), glm::vec3(-0.3f, -0.3f, -0.3f)}, // Bottom Left

            {glm::vec3(1.0f, -1.0f, -1.0f),
             glm::vec2(1.0f, 1.0f), glm::vec3(0.3f, -0.3f, -0.3f)}, //Bottom Right

            {glm::vec3(1.0f, 1.0f, -1.0f),
             glm::vec2(1.0f, 0.0f), glm::vec3(0.3f, 0.3f, -0.3f)}, // Top Right
        };

        indices = {
            0, 1, 2,
            0, 3, 2,

            4, 5, 1,
            4, 1, 0,

            3, 7, 2,
            7, 6, 2,

            1, 5, 2,
            6, 2, 5,

            4, 0, 7,
            0, 7, 3,

            4, 5, 6,
            4, 7, 6};
    }
};

#endif