#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Vector2.h>
#include <Particle.h>
#include <Game.h>
#include <thread>

#include <string>

class Window
{
public:
    Window();
    Window(int x, int y, std::string name);
    ~Window();

    void Update();
    void CheckEvents();
    sf::RenderWindow* GetWindow() { return window; }

    static void Render(std::vector<Particle*>& allParticles, sf::VertexArray& particle_buffer, int threadNb);
    static void SplitThreadRendering(std::vector<Particle*>& allParticles);
private:
    sf::RenderWindow* window{};
    std::vector<Particle*> particles{};
    sf::Text m_text{};
    sf::Font m_font{};

    std::thread renderT1;
    std::thread renderT2;
    std::thread renderT3;
    std::thread renderT4;

    sf::VertexArray particle_buffer1;
    sf::VertexArray particle_buffer2;
    sf::VertexArray particle_buffer3;
    sf::VertexArray particle_buffer4;

    std::thread renderSplitThread;
};

