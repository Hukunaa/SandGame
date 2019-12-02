#include <Game.h>
#include <iostream>
sf::RenderWindow* Game::window;

std::thread Game::RenderingThread;
std::thread Game::PhysicsThread;
std::thread Game::LogicThread;

bool Game::isGameOn;

void Game::SetWindow(sf::RenderWindow* p_window)
{
    window = p_window;
    isGameOn = true;
}

void Game::SpawnParticle(std::vector<Particle*>& particles, ArrData* arr, Particle::STATE state)
{
    Vector2 rawPos = Vector2(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
    Vector2 spawnPos = Vector2::roundVector(rawPos, 4);

    if (rawPos.x > 796 || rawPos.x < 0 || rawPos.y > 796 || rawPos.y < 0)
        return;

    Particle* particle = new Particle(20, 600, 0.1, 0.01, state);

    bool canSpawn = true;
    particle->m_pos = spawnPos;

    if (particle->DoesCollideWith(arr))
        canSpawn = false;

    if (canSpawn)
    {
        particle->SetAlive(true);
        particles.emplace_back(particle);
    }
}

void Game::InitPhysicsThread(ArrData* arr, std::vector<Particle*>& particles, Window* window)
{
    PhysicsThread = std::thread(&Game::UpdatePhysics, std::ref(particles), arr, window);
    PhysicsThread.detach();
}

void Game::UpdatePhysics(std::vector<Particle*>& particles, ArrData* arr, Window* window)
{
    while (true)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            Game::SpawnParticle(particles, arr, Particle::STATE::SOLID);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            Game::SpawnParticle(particles, arr, Particle::STATE::LIQUID);
        }

        window->UpdateArrays(arr, particles);

        for (Particle* particle : particles)
        {
            //particle->mtx.lock();

            if (particle->GetState() == Particle::STATE::LIQUID)
            {
                particle->rawVelocity.y += Environment::gravity_value * particle->particle_details.m_AirDrag;
                particle->m_velocity = Vector2::roundVector(particle->rawVelocity, 4);
                //particle->m_velocity.y = 12;
            }

            if (particle->GetState() == Particle::STATE::SOLID)
                particle->m_velocity.y = 0;

            Vector2 collisionVec;
            if (particle->CheckCollisions(arr, collisionVec))
            {
                particle->m_pos = collisionVec;
            }
            else
                particle->Update();

            //particle->mtx.unlock();

        }
        std::this_thread::sleep_for(std::chrono::microseconds(6900));
    }
}

void Game::UpdateParticles(std::vector<Particle*>& particles, ArrData* arr)
{
    /*while (true)
    {
        for (Particle* particle : particles)
        {
            particle->Update(arr);
        }

        std::this_thread::sleep_for(std::chrono::microseconds(6900));
    }*/

}
