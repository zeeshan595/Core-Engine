#ifndef _CUBE
#define _CUBE

class Cube
{
public:
    static std::vector<Vertex> vertices;
    static std::vector<GLuint> indices;
};
std::vector<Vertex> Cube::vertices = {
    {
        glm::vec3(-1.0f, 1.0f, 1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(-0.3f, 0.3f, 0.3f) 
    },
    {
        glm::vec3(-1.0f, -1.0f, 1.0f), 
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f), 
        glm::vec3(-0.3f, -0.3f, 0.3f)
    },
    {
        glm::vec3(1.0f, -1.0f, 1.0f), 
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f), 
        glm::vec3(0.3f, -0.3f, 0.3f)
    },
    {
        glm::vec3(1.0f, 1.0f, 1.0f), 
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f), 
        glm::vec3(0.3f, 0.3f, 0.3f)
    },
    ///////////////////////////////////////
    {
        glm::vec3(-1.0f, 1.0f, -1.0f),
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec3(-0.3f, 0.3f, 0.3f) 
    },
    {
        glm::vec3(-1.0f, -1.0f, -1.0f), 
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f), 
        glm::vec3(-0.3f, -0.3f, 0.3f)
    },
    {
        glm::vec3(1.0f, -1.0f, -1.0f), 
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec2(1.0f, 1.0f), 
        glm::vec3(0.3f, -0.3f, 0.3f)
    },
    {
        glm::vec3(1.0f, 1.0f, -1.0f), 
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f), 
        glm::vec3(0.3f, 0.3f, 0.3f)
    },
};
std::vector<GLuint> Cube::indices = {
    // front
    0, 1, 2,
    2, 3, 0,
    // top
    1, 5, 6,
    6, 2, 1,
    // back
    7, 6, 5,
    5, 4, 7,
    // bottom
    4, 0, 3,
    3, 7, 4,
    // left
    4, 5, 1,
    1, 0, 4,
    // right
    3, 2, 6,
    6, 7, 3,
};

#endif