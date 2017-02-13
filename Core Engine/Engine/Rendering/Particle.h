#ifndef _PARTICLE
#define _PARTICLE

class Particle
{
public:
    Transform transform;

    Particle()
    {
        
    }
    ~Particle()
    {

    }

private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
};

#include "Particle.c"

#endif