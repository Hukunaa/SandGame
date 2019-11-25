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
    Particle* particle = new Particle(20, 600, 0.1, 0.01, Particle::STATE::SOLID);

    bool canSpawn = true;
    Vector2 spawnPos = Vector2::roundVector(Vector2(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y), 4);
    particle->SetPos(spawnPos);

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

void Game::InitPhysicsThread(std::vector<Particle*>& particles)
{
    PhysicsThread = std::thread(&Game::UpdatePhysics, std::ref(particles));
    PhysicsThread.detach();
}

void Game::UpdatePhysics(std::vector<Particle*>& particles)
{
    while (true)
    {
        for (Particle* particle : particles)
        {
            particle->mtx.lock();

            if(!particle->CheckCollisions(particles))
                particle->m_velocity.y += Environment::gravity_value * particle->particle_details.m_AirDrag;

            particle->Update();
            particle->mtx.unlock();

        }
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}
