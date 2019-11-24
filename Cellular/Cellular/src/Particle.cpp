#include <Particle.h>
#include "..\include\Particle.h"

Particle::Particle(float temp, float fusion_p, float visc, float air_drag, STATE p_type)
{
    m_color = sf::Color(250, 150, 120);

    GetPos() = Vector2::Zero();
    GetMaterial() = sf::RectangleShape({ 1, 1 });
    GetMaterial().setSize({ 4, 4 });
    GetMaterial().setFillColor(m_color);

    particle_details.m_temperature = temp;
    particle_details.m_fusion_point = fusion_p;
    particle_details.m_viscosity = visc;
    particle_details.m_AirDrag = air_drag;
    screenGridPos = 1;
    m_particleType = p_type;
    SetAlive(false);
}

Particle::~Particle()
{
}

void Particle::Update()
{
    m_pos.x += m_velocity.x;
    m_pos.y += m_velocity.y;
    GetMaterial().setPosition({ Vector2::roundUp(m_pos, 4).x, Vector2::roundUp(m_pos, 4).y });
}

bool Particle::DoesCollideWith(Particle& p_mat)
{
    if (p_mat.GetAlive() && p_mat.GetPos().x == GetPos().x && p_mat.GetPos().y == GetPos().y)
        return true;

    return false;
}
