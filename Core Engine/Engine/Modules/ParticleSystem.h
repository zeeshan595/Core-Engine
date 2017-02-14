#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

class ParticleSystem : public Module
{
public:
    std::shared_ptr<Surface> surface;

    ParticleSystem();

    void Render(std::shared_ptr<Camera> camera);
private:
    std::vector<Particle> particles;
    std::vector<glm::mat4x4> particles_matrices;
};

#include "ParticleSystem.c"

#endif