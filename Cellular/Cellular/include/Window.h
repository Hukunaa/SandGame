#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Vector2.h>
#include <Particle.h>
#include <Game.h>
#include <thread>
#include <ParticleManager.h>

#include <string>
#include <mutex>

class Window
{
public:
    Window();
    Window(int x, int y, std::string name);
    ~Window();

    void Update();
    void CheckEvents();
    sf::RenderWindow* GetWindow() { return window; }

    static void Render(std::vector<Particle*>& allParticles, sf::VertexArray& particle_buffer, int threadNb, std::atomic_bool& canDraw, std::atomic_bool& isDrawing);
    static void UpdateArrays(ArrData* arr, std::vector<Particle*>& particles);

private:

    std::atomic_bool canDraw;
    std::atomic_bool isDrawing;

    static std::mutex mtx;

    sf::RenderWindow* window{};
    std::vector<Particle*> particles{};
    sf::Text m_text{};
    sf::Text m_fps{};
    sf::Font m_font{};

    std::thread RenderingThread;
    std::thread ArrayUpdater;

    ArrData* collisionCheck;
    sf::VertexArray particle_buffer1;
};

