Skybox::Skybox()
{
    texture = new CubeTexture("default/skybox_day.png", "default/skybox_day.png", "default/skybox_day.png", "default/skybox_day.png", "default/skybox_day.png", "default/skybox_day.png");
    shader = new Shader("default/skyboxVS.glsl", "default/skyboxFS.glsl");
}

Skybox::~Skybox()
{
    
}

void Skybox::Start()
{
    GenerateBuffers();
}

void Skybox::Stop()
{
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Skybox::Render(Camera* camera)
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
    //view_mat = glm::rotate(view_mat, current_rotation, glm::vec3(0, 1, 0));
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

    //Fog color
    GLint fog_color_uniform = glGetUniformLocation(shader->GetShaderProgram(), "fog_color");
    glUniform4fv(fog_color_uniform, 1, &Fog::fog_color[0]);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Skybox::SetTexture (CubeTexture* texture)
{
    this->texture;
}
void Skybox::SetShader  (Shader* shader)
{
    this->shader = shader;
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
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    //Create EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    
    //Shader Info
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
}