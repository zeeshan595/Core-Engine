GLuint      DefaultResources::plane_VAO        = 0;
GLuint      DefaultResources::plane_VBO        = 0;
GLuint      DefaultResources::plane_EBO        = 0;

GLuint      DefaultResources::cube_VAO        = 0;
GLuint      DefaultResources::cube_VBO        = 0;
GLuint      DefaultResources::cube_EBO        = 0;

void DefaultResources::CreateDefaultResources()
{
    //Create VAO
    glGenVertexArrays(1, &cube_VAO);
    glBindVertexArray(cube_VAO);
    //Create VBO
    glGenBuffers(1, &cube_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);
    glBufferData(GL_ARRAY_BUFFER, Cube::vertices.size() * sizeof(Vertex), Cube::vertices.data(), GL_STATIC_DRAW);
    //Create EBO
    glGenBuffers(1, &cube_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Cube::indices.size() * sizeof(GLuint), Cube::indices.data(), GL_STATIC_DRAW);
    Vertex::AttributeInfo();

    //Create VAO
    glGenVertexArrays(1, &plane_VAO);
    glBindVertexArray(plane_VAO);
    //Create VBO
    glGenBuffers(1, &plane_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, plane_VBO);
    glBufferData(GL_ARRAY_BUFFER, Plane::vertices.size() * sizeof(Vertex), Plane::vertices.data(), GL_STATIC_DRAW);
    //Create EBO
    glGenBuffers(1, &plane_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Plane::indices.size() * sizeof(GLuint), Plane::indices.data(), GL_STATIC_DRAW);
    Vertex::AttributeInfo();
}
void DefaultResources::DestroyDefaultResources()
{
    glDeleteBuffers(1, &cube_EBO);
    glDeleteBuffers(1, &cube_VBO);
    glDeleteVertexArrays(1, &cube_VAO);

    glDeleteBuffers(1, &plane_EBO);
    glDeleteBuffers(1, &plane_VBO);
    glDeleteVertexArrays(1, &plane_VAO);
}

const GLuint        DefaultResources::GetCubeVAO()
{
    return cube_VAO;
}
const GLuint        DefaultResources::GetCubeVBO()
{
    return cube_VBO;
}
const GLuint        DefaultResources::GetCubeEBO()
{
    return cube_EBO;
}

const GLuint        DefaultResources::GetPlaneVAO()
{
    return plane_VAO;
}
const GLuint        DefaultResources::GetPlaneVBO()
{
    return plane_VBO;
}
const GLuint        DefaultResources::GetPlaneEBO()
{
    return plane_EBO;
}