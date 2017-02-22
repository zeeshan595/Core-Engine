#ifndef _PLANE
#define _PLANE

class Plane
{
public:
    static std::vector<Vertex> vertices;
    static std::vector<GLuint> indices;
};
std::vector<Vertex> Plane::vertices{
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
};
std::vector<GLuint> Plane::indices{
    0, 1, 2,
    0, 2, 3
};

#endif