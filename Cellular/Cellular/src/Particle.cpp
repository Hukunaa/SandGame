#include <Particle.h>
#include <iostream>
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

    Vector2 roundedVel = Vector2::roundVector(m_velocity, 4);
    m_pos.x += roundedVel.x;
    m_pos.y += roundedVel.y;

    m_pos = Vector2::roundVector(m_pos, 4);

}


bool Particle::DoesCollideWith(ArrData* arr)
{
    Vector2 pos = Vector2::roundVector(m_pos, 4);
    int x = pos.x / 4;
    int y = pos.y / 4;

    if (arr[y * 200 + x].part != nullptr)
    {
        if(arr[y * 200 + x].part != this)
            return true;
    }
    else
        return false;
    
}

bool Particle::CheckCollisions(ArrData* particles, Vector2& colPos)
{
    bool isColliding = false;

    Vector2 pos = Vector2::roundVector(m_pos, 4);
    //Vector2 vel = Vector2::roundVector(m_velocity, 4);

    Vector2 finalPos;
    finalPos.x = pos.x + m_velocity.x;
    finalPos.y = pos.y + m_velocity.y;

    if (finalPos.y > 400)
    {
        m_velocity.y = 0;
        m_pos.y = 400;
        colPos = m_pos;
        isColliding = true;
        return isColliding;
    }
    int loop = m_velocity.y / 4;

    for(int i = 1; i <= loop; ++i)
    {

        int arrPx = m_pos.x / 4;
        int arrPy = (m_pos.y + (4 * i)) / 4;

        if (particles[arrPy * 200 + arrPx].part != nullptr)
        {
            //particles[arrPy * 800 + arrPx].mtx.lock();
            if (particles[arrPy * 200 + arrPx].part != this)
            {
                isColliding = true;
                colPos.x = m_pos.x;
                colPos.y = m_pos.y + (4 * i) - 4;
                m_velocity.y = 0;
                return isColliding;
            }
            //particles[arrPy * 800 + arrPx].mtx.unlock();
        }
    }
    return false;
}
