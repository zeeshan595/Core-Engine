void MeshRenderer::Start()
{
    if (data == NULL)
    {
        MeshData* mesh_data = entity->GetModule<MeshData>();
        if (mesh_data != NULL)
        {
            data = mesh_data;
        }
        else
        {
            std::cout << "WARNING: mesh render does not have mesh data." << std::endl;
        }
    }
}
void MeshRenderer::Render(Camera* rendering_camera)
{
    if (material != NULL)
    {
        //Light Information
        std::vector<glm::vec3>      light_directions;
        std::vector<glm::vec3>      directional_light_color;

        std::vector<glm::vec3>      light_positions;
        std::vector<glm::vec3>      point_light_color;
        std::vector<float>          light_range;

        //Compute Lighting
        std::vector<Light*> lights = *Environment::GetLights();
        for (uint32_t i = 0; i < lights.size(); i++)
        {
            Light::LIGHT_TYPE light_type = lights[i]->GetLightType();
            if (light_type == Light::LIGHT_TYPE::DIRECTIONAL)
            {
                light_directions.push_back(lights[i]->transform.Forward());
                directional_light_color.push_back(lights[i]->GetLightColor());
            }
            else if (light_type == Light::LIGHT_TYPE::POINT)
            {
                light_positions.push_back(lights[i]->transform.GetPosition());
                point_light_color.push_back(lights[i]->GetLightColor());
                light_range.push_back(lights[i]->GetPointLightRange());
            }
        }

        glUseProgram(material->GetShader()->GetShaderProgram());

        //Camera Projection Matrix
        GLint projection_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "projection_matrix");
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(rendering_camera->GetProjectionMatrix()));

        GLint view_matrix = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "view_matrix");
        glUniformMatrix4fv(view_matrix, 1, GL_FALSE, glm::value_ptr(rendering_camera->GetViewMatrix()));

        GLint transform_matrix = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "transform_matrix");
        glUniformMatrix4fv(transform_matrix, 1, GL_FALSE, glm::value_ptr(entity->transform.GetMatrix()));

        //Lighting
        //Amount Of Directional Lights
        int directional_light_count = light_directions.size();
        GLint light_direction_count_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "directional_light_size");
        glUniform1iv(light_direction_count_uniform, 1, &directional_light_count);
        //Directional Light Vectors
        GLint light_direction_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "directional_light_direction");
        glUniform3fv(light_direction_uniform, light_directions.size(), &light_directions[0][0]);
        //Directional Light Color
        GLint directional_light_color_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "directional_light_color");
        glUniform3fv(directional_light_color_uniform, light_directions.size(), &directional_light_color[0][0]);

        //Amount Of Point Lights
        int point_light_count = light_positions.size();
        GLint point_light_count_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "point_light_size");
        glUniform1iv(point_light_count_uniform, 1, &point_light_count);
        //Point Light Positions
        GLint point_light_position_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "point_light_position");
        glUniform3fv(point_light_position_uniform, light_positions.size(), &light_positions[0][0]);
        //Point Light Color
        GLint point_light_color_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "point_light_color");
        glUniform3fv(point_light_color_uniform, light_positions.size(), &point_light_color[0][0]);
        //Point Light Range
        GLint light_range_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "point_light_range");
        glUniform1fv(light_range_uniform, light_positions.size(), &light_range[0]);

        //Textures
        std::vector<Texture*> textures = (*material->GetTextures());
        for (int i = 0; i < textures.size(); i++)
        {
            std::stringstream ss;
            ss << i;
            std::string texture_name = "texture_map" + ss.str();
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, textures[i]->GetTextureMap());
            GLint texture_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), texture_name.c_str());
            glUniform1i(texture_uniform, i);
        }

        //Additional Material Information
        float material_damper           = material->GetShineDamper();
        float material_reflectivity     = material->GetLightReflectivity();
        GLint shine_damper_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "shine_damper");
        glUniform1fv(shine_damper_uniform, 1, &material_damper);

        GLint light_reflection_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "light_reflectivity");
        glUniform1fv(light_reflection_uniform, 1, &material_reflectivity);

        FogShaderInfo();

        //Draw
        glBindVertexArray(data->GetVAO());
        glDrawElements(GL_TRIANGLES, data->GetIndices().size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        std::cout << "WARNING: No material supplied to the mesh renderer" << std::endl;
    }
}

void MeshRenderer::SetMeshData(MeshData* mesh_data)
{
    this->data = mesh_data;
}
void MeshRenderer::SetMaterial(Material* material)
{
    this->material = material;
}
Material* MeshRenderer::GetMaterial()
{
    return material;
}

void MeshRenderer::FogShaderInfo()
{
    //Fog distance
    GLint fog_distance_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "fog_distance");
    glUniform1fv(fog_distance_uniform, 1, &Fog::distance);
    //Fog density
    GLint fog_density_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "fog_density");
    glUniform1fv(fog_density_uniform, 1, &Fog::density);
    //Fog gradient
    GLint fog_gradient_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "fog_gradient");
    glUniform1fv(fog_gradient_uniform, 1, &Fog::gradient);
    //Fog color
    GLint fog_color_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "fog_color");
    glUniform4fv(fog_color_uniform, 1, &Fog::fog_color[0]);
}