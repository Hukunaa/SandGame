#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Vector2.h>
#include <Particle.h>
#include <string>

class Window
{
public:
    Window();
    Window(int x, int y, std::string name);
    ~Window();

    void Update(std::vector<Particle>& particles);
    void CheckEvents();
    void CheckText(int size);
    sf::RenderWindow* GetWindow() { return window; }

private:
    sf::RenderWindow* window;
    sf::Text m_text;
    sf::Font m_font;
};

