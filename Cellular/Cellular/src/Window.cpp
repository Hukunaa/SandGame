#include <Window.h>
#include <iostream>

Window::Window()
{
    window = new sf::RenderWindow(sf::VideoMode(800, 800), "Default");
    if (!m_font.loadFromFile("include/Minecraft.ttf"))
        std::cout << "CAN'T LOAD FONT FILE!\n";
    m_text.setFont(m_font);
}
Window::Window(int x, int y, std::string name)
{
    window = new sf::RenderWindow(sf::VideoMode(x, y), name);
    if (!m_font.loadFromFile("include/Minecraft.ttf"))
        std::cout << "CAN'T LOAD FONT FILE!\n";
    m_text.setFont(m_font);
}
Window::~Window()
{
    delete window;
}

void Window::Update(std::vector<Particle>& particles)
{
    while (window->isOpen())
    {
        CheckEvents();
        CheckText(particles.size());
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            Particle particle(20, 600, 0.1f, 0.001f, Particle::STATE::SOLID);

            bool canSpawn = true;
            particle.SetPos(Vector2::roundUp(Vector2(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y), 2));

            for (int i = 0; i < particles.size(); ++i)
            {
                if (particle.DoesCollideWith(particles[i]))
                    canSpawn = false;
            }
            if (canSpawn)
            {
                particle.SetAlive(true);
                particles.emplace_back(particle);
            }
        }

        window->clear();
        for (int i = 0; i < particles.size(); ++i)
        {
            particles[i].Update();
            if (particles[i].GetAlive())
            {
                if (particles[i].GetPos().x < 801 && particles[i].GetPos().y < 801)
                {
                    window->draw(particles[i].GetDot());
                    window->draw(m_text);
                }
                else
                {
                    std::vector<Particle>::iterator it = particles.begin();
                    std::advance(it, i);
                    particles.erase(it);
                }
            }
        }

        window->display();
    }
}

void Window::CheckEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
    }
}

void Window::CheckText(int size)
{
    std::string text = std::to_string(size);
    m_text.setCharacterSize(12);
    m_text.setString(text);
}
