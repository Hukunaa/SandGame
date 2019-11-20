#include <Particle.h>

Particle::Particle(float temp, float fusion_p, float visc, float air_drag, STATE p_type)
{
    m_color = sf::Color(250, 150, 120);

    GetPos() = Vector2::Zero();
    GetDot() = sf::RectangleShape({ 1, 1 });
    SetAlive(false);
    GetDot().setSize({ 2, 2 });
    GetDot().setFillColor(m_color);

    particle_details.m_temperature = temp;
    particle_details.m_fusion_point = fusion_p;
    particle_details.m_viscosity = visc;
    particle_details.m_AirDrag = air_drag;

    m_particleType = p_type;
}

Particle::~Particle()
{
}

bool Particle::DoesCollideWith(Particle& p_mat)
{
    if (p_mat.GetAlive() && p_mat.GetPos().x == GetPos().x && p_mat.GetPos().y == GetPos().y)
        return true;

    return false;
}

void Particle::Update()
{
    m_velocity.y += Environment::gravity_value * particle_details.m_AirDrag;

    m_pos.x += m_velocity.x;
    m_pos.y += m_velocity.y;

    GetDot().setPosition({ m_pos.x, m_pos.y });
}
