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
    Particle* particle = new Particle(20, 600, 0.1, 0.0001, Particle::STATE::SOLID);

    bool canSpawn = true;
    particle->SetPos(Vector2::roundUp(Vector2(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y), 4));

    for (int i = 0; i < particles.size(); ++i)
    {
        if (particle->DoesCollideWith(*particles[i]))
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
    /*PhysicsThread = std::thread(&Game::UpdatePhysics, std::ref(particles));
    PhysicsThread.detach();*/
}

void Game::UpdatePhysics(std::vector<Particle*>& particles)
{
    while (1)
    {
        for (int i = 0; i < particles.size(); ++i)
        {
            if (particles[i]->mtx.try_lock())
            {
                particles[i]->m_velocity.y += Environment::gravity_value * particles[i]->particle_details.m_AirDrag;
                particles[i]->mtx.unlock();
            }
        }
    }
}
