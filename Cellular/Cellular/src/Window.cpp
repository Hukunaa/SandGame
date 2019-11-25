#include <Window.h>
#include <iostream>

std::mutex Window::mtx;

Window::Window()
{
}
Window::Window(int x, int y, std::string name)
{
    window = new sf::RenderWindow(sf::VideoMode(x, y), name);

    if (!m_font.loadFromFile("include/Minecraft.ttf"))
        std::cout << "CAN'T LOAD FONT FILE!\n";
    m_text.setFont(m_font);
    particles.reserve(50000);

    canDraw.store(false);
    isDrawing.store(false);

    Game::SetWindow(window);
    Game::InitPhysicsThread(particles);

    particle_buffer1 = sf::VertexArray(sf::Quads);
    renderT1 = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer1), 1, std::ref(canDraw), std::ref(isDrawing));
    renderT1.detach();

}
Window::~Window()
{
    delete window;
}

void Window::Update()
{
    sf::Clock time;
    float oldTime = 0;
    float newTime = 0;
    float DeltaTime = 0;
    while (window->isOpen())
    {
        oldTime = newTime;
        newTime = time.getElapsedTime().asMicroseconds();
        CheckEvents();
        std::string text = std::to_string(particles.size());
        m_text.setCharacterSize(12);
        m_text.setString(text);


        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            Game::SpawnParticle(particles);
        }

        if (particle_buffer1.getVertexCount() > 3 && canDraw.load())
        {
            isDrawing.store(true);
            window->clear();
            window->draw(m_text);
            window->draw(particle_buffer1);
            isDrawing.store(false);
        }
        
        window->display();
        DeltaTime =  1 / ((newTime - oldTime) / 1000000);
        std::cout << "FPS: " << DeltaTime << '\n';
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

void Window::Render(std::vector<Particle*>& allParticles, sf::VertexArray& particle_buffer, int threadNb, std::atomic_bool& canDraw, std::atomic_bool& isDrawing)
{
    while (true)
    {
        if (!isDrawing.load())
        {
            canDraw.store(false);
            particle_buffer.clear();
            for (Particle* particle : allParticles)
            {
                particle->mtx.lock();
                int screenPos = particle->screenGridPos;
                Vector2 roundedPos = Vector2::roundVector(particle->GetPos(), 4);
                particle->mtx.unlock();

                sf::Vector2f partPos(roundedPos.x, roundedPos.y);

                particle_buffer.append(sf::Vertex(sf::Vector2f(partPos.x, partPos.y), sf::Color::Cyan));
                particle_buffer.append(sf::Vertex(sf::Vector2f(partPos.x + 4, partPos.y), sf::Color::Cyan));
                particle_buffer.append(sf::Vertex(sf::Vector2f(partPos.x + 4, partPos.y + 4), sf::Color::Cyan));
                particle_buffer.append(sf::Vertex(sf::Vector2f(partPos.x, partPos.y + 4), sf::Color::Cyan));
            }
            canDraw.store(true);
        }
        
        //Clamp de thread refresh rate by 144FPS, avoinding the thread to use all the CPU Power trying to refresh the buffer an insane amount of times per frame
        std::this_thread::sleep_for(std::chrono::microseconds(6900));
    }
}

/*void Window::SplitThreadRendering(std::vector<Particle*>& allParticles)
{
    while (true)
    {
        if (allParticles.size() > 0)
        {
            for (Particle* particle : allParticles)
            {
                if (particle->m_pos.x < 400 && particle->m_pos.y < 800)
                {
                    particle->mtx.lock();
                    particle->screenGridPos = 1;
                    particle->mtx.unlock();
                }

                if (particle->m_pos.x >= 400 && particle->m_pos.y < 800 && particle->m_pos.x < 800)
                {
                    particle->mtx.lock();
                    particle->screenGridPos = 2;
                    particle->mtx.unlock();
                }

                if (particle->m_pos.x < 400 && particle->m_pos.y >= 400 && particle->m_pos.y < 800)
                    particle->screenGridPos = 3;

                if (particle->m_pos.x >= 400 && particle->m_pos.y >= 400 && particle->m_pos.x < 800 && particle->m_pos.y < 800)
                    particle->screenGridPos = 4;
            }
        }
        std::this_thread::sleep_for(std::chrono::microseconds(6900));
    }
}*/


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

    //renderT2.detach();
    /*renderT3.detach();
    renderT4.detach();*/


    //renderT2 = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer2), 2);
    /*renderT3 = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer3), 3);
    renderT4 = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer4), 4);*/

    //particle_buffer2 = sf::VertexArray(sf::Quads);
    /*particle_buffer3 = sf::VertexBuffer(sf::Quads);
    particle_buffer4 = sf::VertexBuffer(sf::Quads);*/