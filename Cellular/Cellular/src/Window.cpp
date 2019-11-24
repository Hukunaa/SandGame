#include <Window.h>
#include <iostream>

Window::Window()
{
}
Window::Window(int x, int y, std::string name)
{
    window = new sf::RenderWindow(sf::VideoMode(x, y), name);

    if (!m_font.loadFromFile("include/Minecraft.ttf"))
        std::cout << "CAN'T LOAD FONT FILE!\n";
    m_text.setFont(m_font);
    //particles.reserve(2000);

    Game::SetWindow(window);
    Game::InitPhysicsThread(particles);

    particle_buffer1 = sf::VertexArray(sf::Quads);
    //particle_buffer2 = sf::VertexBuffer(sf::Quads);
    /*particle_buffer3 = sf::VertexBuffer(sf::Quads);
    particle_buffer4 = sf::VertexBuffer(sf::Quads);*/

    renderSplitThread = std::thread(&Window::SplitThreadRendering, std::ref(particles));
    renderT1 = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer1), 1);
    //renderT2 = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer2), 2);
    /*renderT3 = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer3), 3);
    renderT4 = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer4), 4);*/
    

    renderSplitThread.detach();
    renderT1.detach();
   // renderT2.detach();
    /*renderT3.detach();
    renderT4.detach();*/

}
Window::~Window()
{
    delete window;
}

void Window::Update()
{
    while (window->isOpen())
    {
        CheckEvents();
        std::string text = std::to_string(particles.size());
        m_text.setCharacterSize(12);
        m_text.setString(text);

        window->clear();
        window->draw(m_text);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            Game::SpawnParticle(particles);
        }
        //std::cout << particle_buffer1.getVertexCount() << "\n";
        window->draw(particle_buffer1);
        /*window->draw(particle_buffer2);
        window->draw(particle_buffer3);
        window->draw(particle_buffer4);*/
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

void Window::Render(std::vector<Particle*>& allParticles, sf::VertexArray& particle_buffer, int threadNb)
{
    while (true)
    {
        particle_buffer.clear();
        for (Particle* particle : allParticles)
        {
            if (particle->screenGridPos.load() == threadNb)
            {
                particle_buffer.append(sf::Vertex(sf::Vector2f(particle->GetPos().x, particle->GetPos().y), sf::Color::Cyan));
                particle_buffer.append(sf::Vertex(sf::Vector2f(particle->GetPos().x + 4, particle->GetPos().y), sf::Color::Yellow));
                particle_buffer.append(sf::Vertex(sf::Vector2f(particle->GetPos().x + 4, particle->GetPos().y + 4), sf::Color::Red));
                particle_buffer.append(sf::Vertex(sf::Vector2f(particle->GetPos().x, particle->GetPos().y + 4), sf::Color::Green));
            }
        }
        
        std::cout << particle_buffer.getVertexCount() << "\n";
        std::this_thread::sleep_for(std::chrono::microseconds(16670));
    }
}

void Window::SplitThreadRendering(std::vector<Particle*>& allParticles)
{
    while (true)
    {
        if (allParticles.size() > 0)
        {
            for (Particle* particle : allParticles)
            {
                if (particle->m_pos.x < 400 && particle->m_pos.y < 800)
                    particle->screenGridPos.store(1);

                if (particle->m_pos.x >= 400 && particle->m_pos.y < 800 && particle->m_pos.x < 800)
                    particle->screenGridPos.store(2);

                /*if (particle->m_pos.x < 400 && particle->m_pos.y >= 400 && particle->m_pos.y < 800)
                    particle->screenGridPos = 3;

                if (particle->m_pos.x >= 400 && particle->m_pos.y >= 400 && particle->m_pos.x < 800 && particle->m_pos.y < 800)
                    particle->screenGridPos = 4;*/
            }
        }
        std::this_thread::sleep_for(std::chrono::microseconds(16670));
    }
}


//for (int i = 0; i < particles.size(); ++i)
//{
    //particles[i]->GetPos().x < window->getSize().x && particles[i]->GetPos().y < window->getSize().y

    /*if (particles[i]->mtx.try_lock())
    {
        particles[i]->Update();
        particles[i]->mtx.unlock();
    }*/
    //window->draw(particles[i]->GetMaterial());

        //std::vector<Particle*>::iterator it = Game::GetParticles().begin();
        //std::advance(it, i);
        //Game::GetParticles().erase(it);
//}
//Draw(particles);
