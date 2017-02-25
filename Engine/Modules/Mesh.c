Mesh::~Mesh()
{
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::Render(std::shared_ptr<Camera> camera)
{
    if (surface != nullptr)
    {
        glUseProgram(surface->GetShader()->GetShaderProgram());
        
        //Camera Projection Matrix
        GLint mvp_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "model_view_projection_matrix");
        glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix() * camera->GetViewMatrix() * attached_to->transform.GetWorldMatrix()));
        
        //World Matrix
        GLint model_to_world_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "model_to_world_matrix");
        glUniformMatrix4fv(model_to_world_uniform, 1, GL_FALSE, &attached_to->transform.GetWorldMatrix()[0][0]);

        //Textures
        std::vector<std::shared_ptr<Texture>>* textures = surface->GetTextures();
        for (int i = 0; i < (*textures).size(); i++)
        {
            std::stringstream ss;
            ss << i;
            std::string texture_name = "texture_map" + ss.str();
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, (*textures)[i]->GetTextureMap());
            GLint texture_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), texture_name.c_str());
            glUniform1i(texture_uniform, i);
        }
        for (int i = (*textures).size(); i < 20; i++)
        {
            std::stringstream ss;
            ss << i;
            std::string texture_name = "texture_map" + ss.str();
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, -1);
            GLint texture_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), texture_name.c_str());
            glUniform1i(texture_uniform, i);
        }
        //Gather Lighting Data
        std::vector<glm::vec3> light_directions;
        std::vector<float> directional_light_brightness;
        std::vector<glm::vec4> directional_light_color;

        std::vector<glm::vec3> light_positions;
        std::vector<float> light_range;
        std::vector<float> point_light_brightness;
        std::vector<glm::vec4> point_light_color;

        for (auto i = (*Environment::GetLights()).begin(); i < (*Environment::GetLights()).end(); i++)
        {
            if ((*i)->type == Light::LIGHT_TYPE::DIRECTIONAL)
            {
                light_directions.push_back((*i)->transform.Forward());
                directional_light_brightness.push_back((*i)->brightness);
                directional_light_color.push_back((*i)->color);
            }
            else if ((*i)->type == Light::LIGHT_TYPE::POINT)
            {
                //if point light is too far away do NOT render it
                if (glm::distance(attached_to->transform.GetPosition(), (*i)->transform.GetPosition()) < ((*i)->light_range * 2) + 5.0f)
                {
                    light_positions.push_back((*i)->transform.GetPosition());
                    light_range.push_back((*i)->light_range);
                    point_light_brightness.push_back((*i)->brightness);
                    point_light_color.push_back((*i)->color);
                }
            }
        }

        //Directional Light
        int directional_light_count = light_directions.size();
        //Directional Data
        GLint light_direction_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "light_directions");
        glUniform3fv(light_direction_uniform, light_directions.size(), &light_directions[0][0]);
        //Amount
        GLint light_direction_count_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "directional_light_count");
        glUniform1iv(light_direction_count_uniform, 1, &directional_light_count);
        //Brightness
        GLint directional_light_brightness_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "directional_light_brightness");
        glUniform1fv(directional_light_brightness_uniform, light_directions.size(), &directional_light_brightness[0]);
        //Color
        GLint directional_light_color_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "directional_light_color");
        glUniform4fv(directional_light_color_uniform, light_directions.size(), &directional_light_color[0][0]);

        //Point Light
        int point_light_size = light_positions.size();
        //Position Data
        GLint light_position_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "light_positions");
        glUniform3fv(light_position_uniform, light_positions.size(), &light_positions[0][0]);
        //Range Data
        GLint light_position_range_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "light_range");
        glUniform1fv(light_position_range_uniform, light_positions.size(), &light_range[0]);
        //Amount
        GLint light_point_count_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "point_light_count");
        glUniform1iv(light_point_count_uniform, 1, &point_light_size);
        //Brightness
        GLint point_light_brightness_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "point_light_brightness");
        glUniform1fv(point_light_brightness_uniform, light_positions.size(), &point_light_brightness[0]);
        //Color
        GLint point_light_color_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "point_light_color");
        glUniform4fv(point_light_color_uniform, light_positions.size(), &point_light_color[0][0]);

        //Camera Position
        GLint eye_position_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "camera_position_world");
        glUniform3fv(eye_position_uniform, 1, &camera->transform.GetPosition()[0]);

        //Fog distance
        GLint fog_distance_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "fog_distance");
        glUniform1fv(fog_distance_uniform, 1, &Fog::distance);
        //Fog density
        GLint fog_density_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "fog_density");
        glUniform1fv(fog_density_uniform, 1, &Fog::density);
        //Fog gradient
        GLint fog_gradient_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "fog_gradient");
        glUniform1fv(fog_gradient_uniform, 1, &Fog::gradient);
        //Fog color
        GLint fog_color_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "fog_color");
        glUniform4fv(fog_color_uniform, 1, &Fog::fog_color[0]);

        Screen::draw_calls++;
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        std::cout << "WARNING: no surface specified. Mesh will not be rendered" << std::endl;
    }
}

void Mesh::LoadOBJFile(std::string filename)
{
    IndexedModel model = OBJModel(MODEL_PATH + filename).ToIndexedModel();
    if (model.positions.size() == model.texCoords.size() && model.texCoords.size() == model.normals.size())
    {
        const int VERTS_LEN = model.positions.size();
        const int INDICES_LEN = model.indices.size();
        vertices.resize(VERTS_LEN);
        indices.resize(INDICES_LEN);

        for (int i = 0; i < VERTS_LEN; i++)
        {
            vertices[i] = {
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
}
void Mesh::LoadDefaultCube()
{
    vertices = Cube::vertices;
    indices = Cube::indices;
    GenerateBuffers();
}
void Mesh::LoadDefaultPlane()
{
    vertices = Plane::vertices;
    indices = Plane::indices;
    GenerateBuffers();
}
void Mesh::CreateMesh(std::vector<Vertex> verts, std::vector<GLuint> ind)
{
    vertices = verts;
    indices = ind;
    GenerateBuffers();
}

void Mesh::GenerateBuffers()
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

    vertices = ComputeVertexTangents(vertices);
    //Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
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

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, tangent));
}

std::vector<Vertex> Mesh::ComputeVertexTangents(std::vector<Vertex> vert)
{
    std::vector<Vertex> vertices = vert;
    for (int i = 0; i < vertices.size() / 3; i++)
    {
        glm::vec3 delta_position1 = vertices[(i*3) + 1].position - vertices[(i*3) + 0].position;
        glm::vec3 delta_position2 = vertices[(i*3) + 2].position - vertices[(i*3) + 0].position;
        glm::vec2 delta_uv1 = vertices[(i*3) + 1].texture - vertices[(i*3) + 0].texture;
        glm::vec2 delta_uv2 = vertices[(i*3) + 2].texture - vertices[(i*3) + 0].texture;

        float r = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv1.y * delta_uv2.x);
        delta_position1 *= delta_uv2.y;
        delta_position2 *= delta_uv1.y;
        glm::vec3 tangent = delta_position1 - delta_position2;
        vertices[(i*3) + 0].tangent = tangent;
        vertices[(i*3) + 1].tangent = tangent;
        vertices[(i*3) + 2].tangent = tangent;
    }

    return vertices;
}

void Mesh::SetSurface(std::shared_ptr<Surface> surface)
{
    this->surface = surface;
}
std::shared_ptr<Surface> Mesh::GetSurface()
{
    return surface;
}