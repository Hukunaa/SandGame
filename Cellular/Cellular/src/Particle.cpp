#include <Particle.h>
#include "..\include\Particle.h"

Particle::Particle(float temp, float fusion_p, float visc, float air_drag, STATE p_type)
{
    m_color = sf::Color(250, 150, 120);

    GetPos() = Vector2::Zero();

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

    //Vector2 roundedPos = m_pos;
    Vector2 roundedPos = Vector2::roundVector(m_pos, 4);
    sf::Vector2f GPUpos(roundedPos.x, roundedPos.y);
}

bool Particle::DoesCollideWith(Particle* p_mat)
{
    sf::Vector2f pos(p_mat->GetPos().x, p_mat->GetPos().y);
    sf::Vector2f matPos(GetPos().x, GetPos().y);

    if (pos.x == matPos.x && pos.y == matPos.y)
        return true;
    
    return false;
}

bool Particle::CheckCollisions(std::vector<Particle*>& particles)
{
    bool isColliding = false;
    sf::Vector2f pos(GetPos().x, GetPos().y);
    sf::Vector2f vel(GetVelocity().x, GetVelocity().y);
    Vector2 finalPos(pos.x + vel.x, pos.y + vel.y);
    if (finalPos.y > 400)
    {
        m_velocity.y = 0;
        isColliding = true;
    }

    for (Particle* particle : particles)
    {
        if (particle != this)
        {
            
            if (Vector2::roundVector(finalPos, 4).x == particle->GetPos().x &&
                Vector2::roundVector(finalPos, 4).y == particle->GetPos().y)
            {
            }
        }
    }

    return isColliding;
}
