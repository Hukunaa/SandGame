#pragma once
#include <Vector2.h>
#include <SFML/Graphics.hpp>
#include <atomic>

#define GRAVITY 9.807

class Material
{
public:
    Material() = default;
    ~Material() = default;

    sf::RectangleShape& GetMaterial() { return m_material; }
    void SetAlive(bool p_value) { is_alive = p_value; }
    std::atomic_bool& GetAlive() { return is_alive; }


private:
    sf::RectangleShape m_material{};
    std::atomic_bool is_alive{ false };

};

