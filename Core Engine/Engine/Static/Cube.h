#ifndef _DEFUALT_CUBE
#define _DEFUALT_CUBE

#include "Vertex.h"

class DefaultCube
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
        //Front
        {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(0.0f, 0.0f), glm::vec3(-0.3f, 0.3f, 0.3f) }, // Top Left

        {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f), glm::vec3(-0.3f, -0.3f, 0.3f)}, // Bottom Left

        {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(1.0f, 1.0f), glm::vec3(0.3f, -0.3f, 0.3f)}, //Bottom Right

        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f)}, // Top Right

        //back
        {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(0.0f, 0.0f), glm::vec3(-0.3f, 0.3f, -0.3f)}, // Top Left

        {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(0.0f, 1.0f), glm::vec3(-0.3f, -0.3f, -0.3f)}, // Bottom Left

        {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(1.0f, 1.0f), glm::vec3(0.3f, -0.3f, -0.3f)}, //Bottom Right

        {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
            glm::vec2(1.0f, 0.0f), glm::vec3(0.3f, 0.3f, -0.3f)}, // Top Right
    };
    std::vector<GLuint> indices = {
        0, 1, 2,
        0, 3, 2,

        4, 5, 1,
        4, 1, 0,

        3, 7, 2,
        7, 6, 2,

        1, 5, 2,
        6, 2, 5,

        4, 0, 7,
        0, 7, 3,

        4, 5, 6,
        4, 7, 6
    };
};

#endif