#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>
#define GRAVITY 9.807

class Material
{
public:
    Material() = default;
    ~Material() = default;

    sf::RectangleShape& GetDot() { return m_dot; }
    void SetAlive(bool p_value) { is_alive = p_value; }
    bool& GetAlive() { return is_alive; }


private:
    sf::RectangleShape m_dot;
    bool is_alive;

};

