Skybox::Skybox()
{
    texture = std::shared_ptr<CubeTexture>(new CubeTexture("left.png", "right.png", "top.png", "bottom.png", "front.png", "back.png"));
    texture2 = std::shared_ptr<CubeTexture>(new CubeTexture("ashcanyon_lf.png", "ashcanyon_rt.png", "ashcanyon_up.png", "ashcanyon_dn.png", "ashcanyon_ft.png", "ashcanyon_bk.png"));
    shader = std::shared_ptr<Shader>(new Shader("default/skyboxVS.glsl", "default/skyboxFS.glsl"));
    if (Skybox::VAO == 0)
        GenerateBuffers();
    
    Skybox::skybox_amount++;
}
Skybox::~Skybox()
{
    Skybox::skybox_amount--;
    if (Skybox::skybox_amount == 0)
    {
        //Delete skybox data
        glDeleteBuffers(1, Skybox::GetEBO());
        glDeleteBuffers(1, Skybox::GetVBO());
        glDeleteVertexArrays(1, Skybox::GetVAO());
    }
}

void Skybox::Render(std::shared_ptr<Camera> camera)
{
    glUseProgram(shader->GetShaderProgram());

    //projection matrix
    GLint projection_uniform = glGetUniformLocation(shader->GetShaderProgram(), "projection_matrix");
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(camera->GetProjectionMatrix()));

    //View matrix (take out the position)
    glm::mat4x4 view_mat = camera->GetViewMatrix();
    view_mat[3][0] = 0;
    view_mat[3][1] = 0;
    view_mat[3][2] = 0;
    view_mat = glm::rotate(view_mat, current_rotation, glm::vec3(0, 1, 0));
    GLint view_uniform = glGetUniformLocation(shader->GetShaderProgram(), "view_matrix");
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view_mat));

    //Cube map texture
    if (texture != nullptr)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture->GetTextureMap());
        GLint texture_uniform = glGetUniformLocation(shader->GetShaderProgram(), "cube_map");
        glUniform1i(texture_uniform, 0);
    }
    //Cube map texture2
    if (texture2 != nullptr)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture2->GetTextureMap());
        GLint texture_uniform2 = glGetUniformLocation(shader->GetShaderProgram(), "cube_map2");
        glUniform1i(texture_uniform2, 1);
    }

    //Blend Amount
    GLint blend_uniform = glGetUniformLocation(shader->GetShaderProgram(), "blend_amount");
    glUniform1fv(blend_uniform, 1, &blend_amount);

    //Fog color
    GLint fog_color_uniform = glGetUniformLocation(shader->GetShaderProgram(), "fog_color");
    glUniform4fv(fog_color_uniform, 1, &Fog::fog_color[0]);

    Screen::draw_calls++;
    glBindVertexArray(Skybox::VAO);
    glDrawElements(GL_TRIANGLES, Skybox::indices.size(), GL_UNSIGNED_INT, 0);
    
    current_rotation += rotation_speed * Time::delta_time;
    if (current_rotation > 360.0f)
        current_rotation = 0.0f;
}

void Skybox::GenerateBuffers()
{
    vertices.resize(Cube::vertices.size());
    for (int i = 0; i < Cube::vertices.size(); i++)
        vertices[i] = Cube::vertices[i].position * 500.0f;
    indices  = {
        // front
        0, 2, 1,
        2, 0, 3,
        // top
        1, 6, 5,
        6, 1, 2,
        // back
        7, 5, 6,
        5, 7, 4,
        // bottom
        4, 3, 0,
        3, 4, 7,
        // left
        4, 1, 5,
        1, 4, 0,
        // right
        3, 6, 2,
        6, 3, 7,
    };
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