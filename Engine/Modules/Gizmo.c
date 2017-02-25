Gizmo::Gizmo()
{
    gizmos_amount++;
    if (gizmos_amount == 1)
    {
        Gizmo::shader = std::shared_ptr<Shader>(new Shader("default/ui_3dVS.glsl", "default/ui_3dFS.glsl"));
        GenerateBuffers();
    }
}

Gizmo::~Gizmo()
{
    gizmos_amount--;
    if (gizmos_amount == 0)
    {
        glDeleteBuffers(1, &Gizmo::EBO);
        glDeleteBuffers(1, &Gizmo::VBO);
        glDeleteVertexArrays(1, &Gizmo::VAO);
    }
}

void Gizmo::Render(std::shared_ptr<Camera> camera)
{
    glDisable(GL_DEPTH_TEST);
    //Setup
    glUseProgram(shader->GetShaderProgram());
    
    //Set rotation of view matrix to default so it faces the camera
    glm::mat4x4 view_matrix = camera->GetViewMatrix();
    glm::mat4x4 world_matrix = glm::translate(glm::mat4x4(1.0f), attached_to->transform.GetPosition());
    world_matrix = glm::scale(world_matrix, glm::vec3(0.5f, 0.5f, 0.5f));

    //Remove rotation by transposing the rotation part of view matrix
    //and storing it intomodel matrix

    world_matrix[0][0] = view_matrix[0][0];
    world_matrix[0][1] = view_matrix[1][0];
    world_matrix[0][2] = view_matrix[2][0];

    world_matrix[1][0] = view_matrix[0][1];
    world_matrix[1][1] = view_matrix[1][1];
    world_matrix[1][2] = view_matrix[2][1];

    world_matrix[2][0] = view_matrix[0][2];
    world_matrix[2][1] = view_matrix[1][2];
    world_matrix[2][2] = view_matrix[2][2];

    glm::mat4x4 mvp_matrix = (camera->GetProjectionMatrix() * view_matrix) * world_matrix;
    GLint mvp_uniform = glGetUniformLocation(shader->GetShaderProgram(), "mvp_matrix");
    glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, glm::value_ptr(mvp_matrix));

    //Texture
    std::string texture_name = "texture_map0";
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->GetTextureMap());
    GLint texture_uniform = glGetUniformLocation(shader->GetShaderProgram(), texture_name.c_str());
    glUniform1i(texture_uniform, 0);

    Screen::draw_calls++;
    glBindVertexArray(Gizmo::VAO);
    glDrawElements(GL_TRIANGLES, Gizmo::indices.size(), GL_UNSIGNED_INT, 0);
    glEnable(GL_DEPTH_TEST);
}

void Gizmo::GenerateBuffers()
{
    Gizmo::vertices = Plane::vertices;
    Gizmo::indices  = Plane::indices;

    //Create VAO
    glGenVertexArrays(1, &Gizmo::VAO);
    glBindVertexArray(Gizmo::VAO);
    //Create VBO
    glGenBuffers(1, &Gizmo::VBO);
    glBindBuffer(GL_ARRAY_BUFFER, Gizmo::VBO);
    glBufferData(GL_ARRAY_BUFFER, Gizmo::vertices.size() * sizeof(Vertex), &Gizmo::vertices[0], GL_STATIC_DRAW);
    //Create EBO
    glGenBuffers(1, &Gizmo::EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Gizmo::EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Gizmo::indices.size() * sizeof(GLuint), &Gizmo::indices[0], GL_STATIC_DRAW);
    
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