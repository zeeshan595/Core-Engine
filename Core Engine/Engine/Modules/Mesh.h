#ifndef _MESH
#define _MESH

#include "Module.h"
#include "../Rendering/Surface.h"
#include "../Static/OBJLoader.h"
#include "../Static/Vertex.h"

class Mesh : public Module
{
public:
    Mesh(){}
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
                    model.positions[i],
                    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
                    model.texCoords[i],
                    model.normals[i]};
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

    void Render(std::shared_ptr<Camera> camera, std::vector<std::shared_ptr<Light>> lights)
    {
        if (surface != nullptr)
        {
            glUseProgram(surface->GetShaderProgram());
            
            //Camera Projection Matrix
            GLint mvp_uniform = glGetUniformLocation(surface->GetShaderProgram(), "model_view_projection_matrix");
            glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix() * camera->GetViewMatrix() * attached_to->transform.GetWorldMatrix()));
            
            //World Matrix
            GLint model_to_world_uniform = glGetUniformLocation(surface->GetShaderProgram(), "model_to_world_matrix");
            glUniformMatrix4fv(model_to_world_uniform, 1, GL_FALSE, &attached_to->transform.GetWorldMatrix()[0][0]);

            //Texture
            if (surface->GetTexture() != nullptr)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, surface->GetTexture()->GetTextureMap());
                GLint texture_uniform = glGetUniformLocation(surface->GetShaderProgram(), "texture_map");
                glUniform1i(texture_uniform, 0);
            }
            //Gather Lighting Data
            std::vector<glm::vec3> light_directions;
            std::vector<float> directional_light_brightness;
            std::vector<glm::vec4> directional_light_color;

            std::vector<glm::vec3> light_positions;
            std::vector<float> light_range;
            std::vector<float> point_light_brightness;
            std::vector<glm::vec4> point_light_color;

            for (auto i = lights.begin(); i < lights.end(); i++)
            {
                if ((*i)->light_type == Light::LIGHT_TYPE::DIRECTIONAL)
                {
                    light_directions.push_back((*i)->transform.Forward());
                    directional_light_brightness.push_back((*i)->brightness);
                    directional_light_color.push_back((*i)->color);
                }
                else if ((*i)->light_type == Light::LIGHT_TYPE::POINT)
                {
                    if (glm::distance(attached_to->transform.position, (*i)->transform.position) < (*i)->light_range * 2)
                    {
                        light_positions.push_back((*i)->transform.position);
                        light_range.push_back((*i)->light_range);
                        point_light_brightness.push_back((*i)->brightness);
                        point_light_color.push_back((*i)->color);
                    }
                }
            }

            //Directional Light
            int directional_light_count = light_directions.size();
            //Directional Data
            GLint light_direction_uniform = glGetUniformLocation(surface->GetShaderProgram(), "light_directions");
            glUniform3fv(light_direction_uniform, light_directions.size(), &light_directions[0][0]);
            //Amount
            GLint light_direction_count_uniform = glGetUniformLocation(surface->GetShaderProgram(), "directional_light_count");
            glUniform1iv(light_direction_count_uniform, 1, &directional_light_count);
            //Brightness
            GLint directional_light_brightness_uniform = glGetUniformLocation(surface->GetShaderProgram(), "directional_light_brightness");
            glUniform1fv(directional_light_brightness_uniform, light_directions.size(), &directional_light_brightness[0]);
            //Color
            GLint directional_light_color_uniform = glGetUniformLocation(surface->GetShaderProgram(), "directional_light_color");
            glUniform4fv(directional_light_color_uniform, light_directions.size(), &directional_light_color[0][0]);

            //Point Light
            int point_light_size = light_positions.size();
            //Position Data
            GLint light_position_uniform = glGetUniformLocation(surface->GetShaderProgram(), "light_positions");
            glUniform3fv(light_position_uniform, light_positions.size(), &light_positions[0][0]);
            //Range Data
            GLint light_position_range_uniform = glGetUniformLocation(surface->GetShaderProgram(), "light_range");
            glUniform1fv(light_position_range_uniform, light_positions.size(), &light_range[0]);
            //Amount
            GLint light_point_count_uniform = glGetUniformLocation(surface->GetShaderProgram(), "point_light_count");
            glUniform1iv(light_point_count_uniform, 1, &point_light_size);
            //Brightness
            GLint point_light_brightness_uniform = glGetUniformLocation(surface->GetShaderProgram(), "point_light_brightness");
            glUniform1fv(point_light_brightness_uniform, light_positions.size(), &point_light_brightness[0]);
            //Color
            GLint point_light_color_uniform = glGetUniformLocation(surface->GetShaderProgram(), "point_light_color");
            glUniform4fv(point_light_color_uniform, light_positions.size(), &point_light_color[0][0]);

            //Camera Position
            GLint eye_position_uniform = glGetUniformLocation(surface->GetShaderProgram(), "camera_position_world");
            glUniform3fv(eye_position_uniform, 1, &camera->transform.position[0]);
            

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        }
        else
        {
            std::cout << "WARNING: surface is null asigning simpleVS & simpleFS" << std::endl;
            surface = std::shared_ptr<Surface>(new Surface("defaultVS.glsl", "defaultFS.glsl"));
        }
    }

    void LoadDefaultCube()
    {
        verts = {
            //Front
            {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
             glm::vec2(0.0f, 0.0f), glm::vec3(-0.3f, 0.3f, 0.3f) }, // Top Left

            {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
             glm::vec2(0.0f, 1.0f), glm::vec3(-0.3f, -0.3f, 0.3f)}, // Bottom Left

            {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
             glm::vec2(1.0f, 1.0f), glm::vec3(0.3f, -0.3f, 0.3f)}, //Bottom Right

            {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
             glm::vec2(1.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f)}, // Top Right

            //back
            {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
             glm::vec2(0.0f, 0.0f), glm::vec3(-0.3f, 0.3f, -0.3f)}, // Top Left

            {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
             glm::vec2(0.0f, 1.0f), glm::vec3(-0.3f, -0.3f, -0.3f)}, // Bottom Left

            {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
             glm::vec2(1.0f, 1.0f), glm::vec3(0.3f, -0.3f, -0.3f)}, //Bottom Right

            {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
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
            4, 7, 6
        };

        GenerateBuffers();
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
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texture));
    
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    }
};

#endif