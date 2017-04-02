void UI::Start()
{
     vertices  = {
        {  0,  1, 0 },
        {  0,  0, 0 },
        {  1,  1, 0 },
        {  1,  0, 0 }
    };
    indices = {
        0, 1, 2,
        1, 3, 2
    };

    //Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    //Create EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    //Shader Info
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
}

void UI::Stop()
{
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void UI::Render(Camera* rendering_camera)
{
    glUseProgram(shader->GetShaderProgram());

    GLint transform_matrix = glGetUniformLocation(shader->GetShaderProgram(), "transform_matrix");
    glUniformMatrix4fv(transform_matrix, 1, GL_FALSE, glm::value_ptr(entity->transform.GetMatrix()));

    //Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->GetTextureMap());
    GLint texture_uniform = glGetUniformLocation(shader->GetShaderProgram(), "texture_map");
    glUniform1i(texture_uniform, 0);

    //Draw
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void UI::SetTexture(Texture* t)
{
    texture = t;
}
Texture*    UI::GetTexture()
{
    return texture;
}

void UI::SetShader(Shader* s)
{
    shader = s;
}
Shader*     UI::GetShader()
{
    return shader;
}