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


bool Particle::DoesCollideWith(Particle* p_mat)
{
    Vector2 pos = Vector2::roundVector(m_pos, 4);
    Vector2 posB = Vector2::roundVector(p_mat->m_pos, 4);

    if (pos.x == posB.x && pos.y == posB.y)
        return true;
    
    return false;
}

bool Particle::CheckCollisions(ArrData* particles, Vector2& colPos)
{
    bool isColliding = false;
    /*sf::Vector2f pos(GetPos().x, GetPos().y);
    sf::Vector2f vel(GetVelocity().x, GetVelocity().y);*/
    //Vector2 roundedVelocity = Vector2::roundVector(Vector2(vel.x, vel.y), 4);
    //float roundedMagnitude = roundedVelocity.GetMagnitude();


    /*Vector2 finalPos(pos.x + vel.x, pos.y + vel.y);
    finalPos = Vector2::roundVector(finalPos, 4);*/
    Vector2 pos = Vector2::roundVector(m_pos, 4);
    Vector2 vel = Vector2::roundVector(m_velocity, 4);

    Vector2 finalPos;
    finalPos.x = pos.x + vel.x;
    finalPos.y = pos.y + vel.y;

    if (finalPos.y > 400)
    {
        m_velocity.y = 0;
        m_pos.y = 400;
        colPos = m_pos;
        isColliding = true;
        return isColliding;
    }

    Vector2 predictedVector;
    predictedVector.x = pos.x + vel.x;
    predictedVector.y = pos.y + vel.y;

    int arrPx = predictedVector.x / 4;
    int arrPy = predictedVector.y / 4;

    if (particles[arrPy * 200 + arrPx].part != nullptr)
    {
        //particles[arrPy * 800 + arrPx].mtx.lock();
        if (particles[arrPy * 200 + arrPx].part != this)
        {
            isColliding = true;
            colPos.x = predictedVector.x - vel.x;
            colPos.y = predictedVector.y - vel.y;
            return isColliding;
        }
        //particles[arrPy * 800 + arrPx].mtx.unlock();
    }
    /*for (int i = 0; i < vel.y; ++i)
    {
        Vector2 tmpVel;
        tmpVel.x = (vel.x) * i;
        tmpVel.y = (vel.y) * i;

        Vector2 predictedVector;
        predictedVector.x = pos.x + tmpVel.x;
        predictedVector.y = pos.y + tmpVel.y;

        int arrPx = predictedVector.x;
        int arrPy = predictedVector.y;

        if (particles[arrPy * 800 + arrPx].part != nullptr)
        {
            //particles[arrPy * 200 + arrPx].mtx.lock();
            if(particles[arrPy * 800 + arrPx].part != this)
            {
                isColliding = true;
                colPos = predictedVector;
                return isColliding;
            }
            //particles[arrPy * 200 + arrPx].mtx.unlock();
        }

    }*/
    return isColliding;
}
