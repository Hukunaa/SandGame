#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <thread>

#include <Material.h>
#include <Particle.h>
#include <Window.h>

int main()
{
    Window Context;
    std::vector<Particle> particles;
    Context.Update(particles);
    return 0;
}