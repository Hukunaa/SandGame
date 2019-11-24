#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <Window.h>
#include <Particle.h>
#include <thread>
#include <mutex>

class Game
{
public:
    //static std::vector<Particle*>& GetParticles() { return particles; }
    //static std::mutex& GetMutex() { return mtx; }

    static void SetWindow(sf::RenderWindow* window);
    static void SpawnParticle(std::vector<Particle*>& particles);
    static void InitPhysicsThread(std::vector<Particle*>& particles);
    static void UpdatePhysics(std::vector<Particle*>& particles);

    static bool isGameOn;
private:

    static sf::RenderWindow* window;

    static std::thread RenderingThread;
    static std::thread PhysicsThread;
    static std::thread LogicThread;

};

