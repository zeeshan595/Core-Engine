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
        glUseProgram(material->GetShader()->GetShaderProgram());

        //Camera Projection Matrix
        GLint projection_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "projection_matrix");
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(rendering_camera->GetProjectionMatrix()));

        GLint view_matrix = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "view_matrix");
        glUniformMatrix4fv(view_matrix, 1, GL_FALSE, glm::value_ptr(rendering_camera->GetViewMatrix()));

        GLint transform_matrix = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "transform_matrix");
        glUniformMatrix4fv(transform_matrix, 1, GL_FALSE, glm::value_ptr(entity->transform.GetMatrix()));
        
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

        //Camera Position
        GLint eye_position_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "camera_position");
        glUniform3fv(eye_position_uniform, 1, &rendering_camera->transform.GetPosition()[0]);
        LightShaderInfo();
        FogShaderInfo();

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

void MeshRenderer::LightShaderInfo()
{
    //Gather Lighting Data
    std::vector<glm::vec3>      light_directions;
    std::vector<float>          directional_light_brightness;
    std::vector<glm::vec4>      directional_light_color;

    std::vector<glm::vec3>      light_positions;
    std::vector<float>          point_light_brightness;
    std::vector<glm::vec4>      point_light_color;
    std::vector<float>          light_range;

    std::vector<Light*> lights = *Environment::GetLights();
    for (uint32_t i = 0; i < lights.size(); i++)
    {
        Light::LIGHT_TYPE light_type = lights[i]->GetLightType();
        if (light_type == Light::LIGHT_TYPE::DIRECTIONAL)
        {
            light_directions.push_back(lights[i]->transform.Forward());
            directional_light_brightness.push_back(lights[i]->GetLightBrightness());
            directional_light_color.push_back(lights[i]->GetLightColor());
        }
        else if (light_type == Light::LIGHT_TYPE::POINT)
        {
            light_positions.push_back(lights[i]->transform.GetPosition());
            point_light_brightness.push_back(lights[i]->GetLightBrightness());
            point_light_color.push_back(lights[i]->GetLightColor());
            light_range.push_back(lights[i]->GetPointLightRange());
        }
    }

    //Directional Light
    int directional_light_count = light_directions.size();
    //Directional Data
    GLint light_direction_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "light_directions");
    glUniform3fv(light_direction_uniform, light_directions.size(), &light_directions[0][0]);
    //Amount
    GLint light_direction_count_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "directional_light_count");
    glUniform1iv(light_direction_count_uniform, 1, &directional_light_count);
    //Brightness
    GLint directional_light_brightness_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "directional_light_brightness");
    glUniform1fv(directional_light_brightness_uniform, light_directions.size(), &directional_light_brightness[0]);
    //Color
    GLint directional_light_color_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "directional_light_color");
    glUniform4fv(directional_light_color_uniform, light_directions.size(), &directional_light_color[0][0]);

    //Point Light
    int point_light_size = light_positions.size();
    //Position Data
    GLint light_position_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "light_positions");
    glUniform3fv(light_position_uniform, light_positions.size(), &light_positions[0][0]);
    //Range Data
    GLint light_position_range_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "light_range");
    glUniform1fv(light_position_range_uniform, light_positions.size(), &light_range[0]);
    //Amount
    GLint light_point_count_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "point_light_count");
    glUniform1iv(light_point_count_uniform, 1, &point_light_size);
    //Brightness
    GLint point_light_brightness_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "point_light_brightness");
    glUniform1fv(point_light_brightness_uniform, light_positions.size(), &point_light_brightness[0]);
    //Color
    GLint point_light_color_uniform = glGetUniformLocation(material->GetShader()->GetShaderProgram(), "point_light_color");
    glUniform4fv(point_light_color_uniform, light_positions.size(), &point_light_color[0][0]);
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