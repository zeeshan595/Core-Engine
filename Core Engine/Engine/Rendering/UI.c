UI::UI(std::shared_ptr<Texture> tex, glm::vec4 ui_rect)
{
    UI::ui_amount++;
    texture = tex;
    rect = ui_rect;
    rotation = 0;
    if (UI::shader == nullptr)
        GenerateBuffers();
}
UI::~UI()
{
    UI::ui_amount--;
    if (UI::ui_amount == 0)
    {
        //Delete ui data
        glDeleteBuffers(1, UI::GetEBO());
        glDeleteBuffers(1, UI::GetVBO());
        glDeleteVertexArrays(1, UI::GetVAO());
    }
}

void UI::PreRender()
{
    glUseProgram(UI::shader->GetShaderProgram());
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(UI::VAO);
}
void UI::Render()
{
    //ui_position
    GLint ui_position_uniform = glGetUniformLocation(UI::shader->GetShaderProgram(), "ui_transformation");
    glUniformMatrix4fv(ui_position_uniform, 1, GL_FALSE, glm::value_ptr(GetTransformationMatrix()));

    //Textures
    if (texture != nullptr)
    {
        glBindTexture(GL_TEXTURE_2D, texture->GetTextureMap());
        GLint texture_uniform = glGetUniformLocation(UI::shader->GetShaderProgram(), "ui_texture_map");
        glUniform1i(texture_uniform, 0);
    }

    Screen::draw_calls++;
    glDrawElements(GL_TRIANGLES, UI::indices.size(), GL_UNSIGNED_INT, 0);
}

void UI::GenerateBuffers()
{
    UI::vertices  = {
        {  0,  1 },
        {  0,  0 },
        {  1,  1 },
        {  1,  0 }
    };
    UI::indices = {
        0, 1, 2,
        1, 3, 2
    };
    UI::shader = std::shared_ptr<Shader>(new Shader("default/uiVS.glsl","default/uiFS.glsl"));
    //Create VAO
    glGenVertexArrays(1, &UI::VAO);
    glBindVertexArray(UI::VAO);
    //Create VBO
    glGenBuffers(1, &UI::VBO);
    glBindBuffer(GL_ARRAY_BUFFER, UI::VBO);
    glBufferData(GL_ARRAY_BUFFER, UI::vertices.size() * sizeof(glm::vec2), &UI::vertices[0], GL_STATIC_DRAW);
    //Create EBO
    glGenBuffers(1, &UI::EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UI::EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, UI::indices.size() * sizeof(GLuint), &UI::indices[0], GL_STATIC_DRAW);
    
    //Shader Info
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0);
}

glm::mat4x4 UI::GetTransformationMatrix()
{
    glm::vec4 mapped_rect = rect;
    mapped_rect = glm::vec4(mapped_rect.x / Screen::width, mapped_rect.y / Screen::height, mapped_rect.z / Screen::width, mapped_rect.w  / Screen::height);
    mapped_rect.x = (mapped_rect.x * 2.0f) - 1.0f;
    mapped_rect.y = 1.0 - ((mapped_rect.y * 2.0f) + mapped_rect.w);

    glm::mat4x4 model_matrix = glm::mat4x4(1.0f);
    model_matrix = glm::translate(model_matrix, glm::vec3(mapped_rect.x, mapped_rect.y, 0.0f));
    model_matrix = glm::rotate(model_matrix, rotation, glm::vec3(0, 0, 1.0f));
    model_matrix = glm::scale(model_matrix, glm::vec3(mapped_rect.z, mapped_rect.w, 0.0f));
    return model_matrix;
}