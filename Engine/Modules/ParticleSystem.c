void ParticleSystem::Render(std::shared_ptr<Camera> camera)
{
    if (particles.size() > 100)
    {
        std::cout << "1 System can can have a max of 100 particles at one time" << std::endl;
        return;
    }

    if (surface != nullptr)
    {
        //Setup
        glUseProgram(surface->GetShader()->GetShaderProgram());
        if (use_blending)
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        }
        
        //Get Particle Matrices
        particles_matrices.resize(particles.size());
        glm::mat4x4 view_matrix = camera->GetViewMatrix();
        for (int i = 0; i < particles_matrices.size(); i++)
        {
            glm::mat4x4 parent_matrix = glm::translate(glm::mat4(1.0), attached_to->transform.GetPosition());
            particles_matrices[i] = parent_matrix * particles[i].transform.GetWorldMatrix();
            
            //Remove rotation by transposing the rotation part of view matrix
            //and storing it intomodel matrix
            particles_matrices[i][0][0] = view_matrix[0][0];
            particles_matrices[i][0][1] = view_matrix[1][0];
            particles_matrices[i][0][2] = view_matrix[2][0];

            particles_matrices[i][1][0] = view_matrix[0][1];
            particles_matrices[i][1][1] = view_matrix[1][1];
            particles_matrices[i][1][2] = view_matrix[2][1];

            particles_matrices[i][2][0] = view_matrix[0][2];
            particles_matrices[i][2][1] = view_matrix[1][2];
            particles_matrices[i][2][2] = view_matrix[2][2];
        }

        //Camera Projection Matrix
        GLint vp_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "view_projection_matrix");
        glUniformMatrix4fv(vp_uniform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix() * view_matrix));

        //Particles world matrices
        GLint world_matrix_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), "world_matrices");
        glUniformMatrix4fv(world_matrix_uniform, particles_matrices.size(), GL_FALSE, glm::value_ptr(particles_matrices[0]));

        //Texture
        std::string texture_name = "texture_map0";
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (*surface->GetTextures())[0]->GetTextureMap());
        GLint texture_uniform = glGetUniformLocation(surface->GetShader()->GetShaderProgram(), texture_name.c_str());
        glUniform1i(texture_uniform, 0);

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
        glBindVertexArray(Particle::GetVAO());
        glDrawElementsInstanced(GL_TRIANGLES, (*Particle::GetIndices()).size(), GL_UNSIGNED_INT, 0, particles.size());
        glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
    }
    else
    {
        std::cout << "WARNING: no surface specified. particles will not be rendered" << std::endl;
    }
}

void ParticleSystem::Update()
{
    if (particles.size() != max_particles)
    {
        if (max_particles > 10000)
        {
            std::cout << "WARNING: 1 Particle System can only have 10,000 particles." << std::endl;
            return;
        }
        particles.resize(max_particles);
    }
    
    for (int i = 0; i < particles.size(); i++)
    {
        if (particles[i].transform.GetSize().x == 0 && current_time > spawn_period)
        {
            CreateParticle(i);
        }

        particles[i].current_time += Time::delta_time;
        particles[i].velocity.y -= gravity * Time::delta_time;
        particles[i].transform.Translate(particles[i].transform.GetPosition() + particles[i].velocity * Time::delta_time);
        if (particles[i].current_time > death_time)
            particles[i].transform.Scale(glm::vec3(0, 0, 0));
    }

    current_time += Time::delta_time;
}

void ParticleSystem::CreateParticle(int i)
{
    //Position
    float rand_position_x = RandomFloat(position_x.x, position_x.y);
    float rand_position_y = RandomFloat(position_y.x, position_y.y);
    float rand_position_z = RandomFloat(position_z.x, position_z.y);

    float rand_rotation = RandomFloat(rotation.x, rotation.y);
    float rand_scale = RandomFloat(size.x, size.y);

    float rand_velocity_x = RandomFloat(velocity_x.x, velocity_x.y);
    float rand_velocity_y = RandomFloat(velocity_y.x, velocity_y.y);
    float rand_velocity_z = RandomFloat(velocity_z.x, velocity_z.y);

    particles[i].transform.Translate(glm::vec3(rand_position_x, rand_position_y, rand_position_z));
    particles[i].transform.Rotate(glm::vec3(0, 0, rand_rotation));
    particles[i].transform.Scale(glm::vec3(rand_scale, rand_scale, rand_scale));
    particles[i].velocity = glm::vec3(rand_velocity_x, rand_velocity_y, rand_velocity_z);
    particles[i].current_time = 0;
    current_time = 0;
}


float ParticleSystem::RandomFloat(float a, float b)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

ParticleSystem::ParticleSystem()
{
    position_x = glm::vec2(-1.5, 1.5);
    position_y = glm::vec2(0, 0);
    position_z = glm::vec2(-1.5, 1.5);
    rotation = glm::vec2(0, 0);
    size = glm::vec2(0.3f, 0.5);
    velocity_x = glm::vec2(-0.5, 0.5);
    velocity_y = glm::vec2(7, 10);
    velocity_z = glm::vec2(-0.5, 0.5);

    max_particles = 25;
    gravity = 9.8f;
    death_time = 2.0f;
    spawn_period = 0.3f;
    use_blending = false;
}