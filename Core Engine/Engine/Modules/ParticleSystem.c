void ParticleSystem::Render(std::shared_ptr<Camera> camera)
{
    if (particles.size() > 10000)
    {
        std::cout << "1 System can can have a max of 100,000 particles at one time" << std::endl;
        return;
    }

    if (surface != nullptr)
    {
        //Setup
        glUseProgram(surface->GetShader()->GetShaderProgram());
        GLuint VAO = Particle::GetVAO();
        std::vector<GLuint> indices = (*Particle::GetIndices());
        glBindVertexArray(VAO);
        std::vector<std::shared_ptr<Texture>>* textures = surface->GetTextures();
        glBindTexture(GL_TEXTURE_2D, (*textures)[0]->GetTextureMap());
        
        //Get Particle Matrices
        particles_matrices.resize(particles.size());
        for (int i = 0; i < particles_matrices.size(); i++)
            particles_matrices[i] = particles[i].transform.GetWorldMatrix();

        int particles_count = particles_matrices.size();

        //Camera Projection Matrix
        GLint vp_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "view_projection_matrix");
        glUniformMatrix4fv(vp_uniform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix() * camera->GetViewMatrix()));

        //Particles world matrices
        GLint world_matrix_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "world_matrices");
        glUniformMatrix4fv(world_matrix_uniform, particles_matrices.size(), GL_FALSE, glm::value_ptr(particles_matrices[0]));

        //Texture
        std::string texture_name = "texture_map0";
        glActiveTexture(GL_TEXTURE0);
        GLint texture_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), texture_name.c_str());
        glUniform1i(texture_uniform, 0);

        Screen::draw_calls++;
        glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, particles.size());
    }
    else
    {
        std::cout << "WARNING: no surface specified. particles will not be rendered" << std::endl;
    }
}

ParticleSystem::ParticleSystem()
{
    surface = std::shared_ptr<Surface>(new Surface(std::shared_ptr<Shader>(new Shader("default/particleVS.glsl", "default/particleFS.glsl"))));
    surface->ApplyTexture(std::shared_ptr<Texture>(new Texture("texture.png")));
    particles.resize(1);
    //particles[1].transform.position = glm::vec3(2.0f, 0.0f, 0.0f);
}