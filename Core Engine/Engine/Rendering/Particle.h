#ifndef _PARTICLE
#define _PARTICLE

class Particle
{
public:
    Transform transform;

    glm::vec3 velocity;
    float current_time;

    Particle();
    ~Particle();

    static GLuint GetVAO(){
        return Particle::VAO;
    }
    static GLuint GetEBO(){
        return Particle::EBO;
    }
    static GLuint GetVBO(){
        return Particle::VBO;
    }
    static std::vector<Vertex>* GetVertices(){
        return &Particle::vertices;
    }
    static std::vector<GLuint>* GetIndices(){
        return &Particle::indices;
    }

private:
    static std::vector<Vertex> vertices;
    static std::vector<GLuint> indices;
    static GLuint VBO;
    static GLuint EBO;
    static GLuint VAO;
    static int particles_amount;

    void GenerateBuffers();
};
std::vector<Vertex> Particle::vertices;
std::vector<GLuint> Particle::indices;
GLuint Particle::VBO;
GLuint Particle::EBO;
GLuint Particle::VAO;
int Particle::particles_amount;

#include "Particle.c"

#endif