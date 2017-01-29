#ifndef _PLANE
#define _PLANE

class DefualtPlane
{
public:
    std::vector<Vertex> GetVertices(){
        return verts;
    }
    std::vector<GLuint> GetIndices(){
        return indices;
    }

private:
    std::vector<Vertex> verts = {
        //back
        {glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, -1.0f)}, // Top Left

        {glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, -1.0f)}, // Bottom Left

        {glm::vec3(1.0f, -1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, -1.0f)}, //Bottom Right

        {glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, -1.0f)}, // Top Right
    };
    std::vector<GLuint> indices = {
        0, 2, 1,
        0, 2, 3
    };
};

#endif