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

void Game::SpawnParticle(std::vector<Particle*>& particles)
{
    Vector2 spawnPos = Vector2::roundVector(Vector2(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y), 4);
    if (spawnPos.x > 800 || spawnPos.x < 0 || spawnPos.y > 799 && spawnPos.y < 1)
        return;

    Particle* particle = new Particle(20, 600, 0.1, 0.01, Particle::STATE::SOLID);

    bool canSpawn = true;
    particle->m_pos = spawnPos;

    for (int i = 0; i < particles.size(); ++i)
    {
        if (particle->DoesCollideWith(particles[i]))
            canSpawn = false;
    }
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
        window->UpdateArrays(arr, particles);
        for (Particle* particle : particles)
        {
            //particle->mtx.lock();

            //particle->m_velocity.y += Environment::gravity_value * particle->particle_details.m_AirDrag;
            //particle->m_Rvelocity = Vector2::roundVector(particle->m_velocity, 4);
            particle->m_velocity.y = 4;
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
