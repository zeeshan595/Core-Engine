#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

class ParticleSystem : public Module
{
public:
    float particle_amount;
    glm::vec2 velocity_x;
    glm::vec2 velocity_y;
    glm::vec2 velocity_z;
    float gravity;
    float death_time = 2.0f;
    float size = 0.3f;
    std::shared_ptr<Surface> surface;

    ParticleSystem();

    void Render(std::shared_ptr<Camera> camera);
    void Update();

private:
    std::vector<Particle> particles;
    std::vector<glm::mat4x4> particles_matrices;

    float RandomFloat(float a, float b);
};

#include "ParticleSystem.c"

#endif