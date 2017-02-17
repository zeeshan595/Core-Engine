#ifndef _PARTICLE_SYSTEM
#define _PARTICLE_SYSTEM

class ParticleSystem : public Module
{
public:
    float max_particles;
    
    //Position
    glm::vec2 position_x;
    glm::vec2 position_y;
    glm::vec2 position_z;
    //Rotation
    glm::vec2 rotation;    
    //Scale
    glm::vec2 size;

    //velocity
    glm::vec2 velocity_x;
    glm::vec2 velocity_y;
    glm::vec2 velocity_z;

    float gravity;
    float death_time;
    float spawn_period;
    bool use_blending;

    ParticleSystem();

    void Render(std::shared_ptr<Camera> camera);
    void Update();
    void ApplySurface(std::shared_ptr<Surface> s){
        surface = s;
    }
    std::shared_ptr<Surface> GetSurface(){
        return surface;
    }

private:
    float current_time;
    std::vector<Particle> particles;
    std::vector<glm::mat4x4> particles_matrices;
    std::shared_ptr<Surface> surface;

    void CreateParticle(int i);
    float RandomFloat(float a, float b);
};

#include "ParticleSystem.c"

#endif