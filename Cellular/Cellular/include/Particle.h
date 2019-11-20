#pragma once
#include <Material.h>
#include <Environment.h>

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

    STATE& GetType() { return m_particleType; }
    Vector2& GetPos() { return m_pos; }
    Vector2& GetVelocity() { return m_velocity; }
    bool DoesCollideWith(Particle& p_mat);

    void Update();
    void SetPos(Vector2 p_pos) { m_pos = p_pos; }
private:

    Environment::particle_args particle_details;
    Vector2 m_pos;
    Vector2 m_velocity;
    sf::Color m_color;
    STATE m_particleType;
};

