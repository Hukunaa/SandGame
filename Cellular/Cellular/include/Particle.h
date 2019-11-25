#pragma once
#include <Material.h>
#include <Environment.h>
#include <mutex>

class Particle : public Material
{
public:

    //During Type transition, it can go from solid -> liquid, liquid -> gas, and inverse
    enum STATE
    {
        SOLID,
        LIQUID,
        GAS
    };

    Particle() = default;

    Particle(float temp, float fusion_p, float visc, float air_drag, STATE p_type);
    ~Particle();

    void Update();

    STATE& GetType() { return m_particleType; }
    Vector2& GetPos() { return m_pos; }
    Vector2& GetVelocity() { return m_velocity; }
    Environment::particle_args& GetDetails() { return particle_details; }

    bool DoesCollideWith(Particle* p_mat);
    bool CheckCollisions(std::vector<Particle*>& particles);
    void SetPos(Vector2 p_pos) { m_pos = p_pos; }

    Vector2 m_velocity{};
    Vector2 m_pos{};
    std::mutex mtx;

    Environment::particle_args particle_details{};
    int screenGridPos;
private:

    sf::Color m_color{};
    STATE m_particleType{};
};



    /*Particle(const Particle& part)
    {
        particle_details = part.particle_details;
        m_pos = part.m_pos;
        m_velocity = part.m_velocity;
        m_color = part.m_color;
        m_particleType = part.m_particleType;
    }*/