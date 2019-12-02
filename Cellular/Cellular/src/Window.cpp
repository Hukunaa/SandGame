#include <Window.h>
#include <iostream>

std::mutex Window::mtx;

Window::Window()
{
}
Window::Window(int x, int y, std::string name)
{
    window = new sf::RenderWindow(sf::VideoMode(x, y), name);
    collisionCheck = new ArrData[40000];

    for (int i = 0; i < 40000; ++i)
        collisionCheck[i].part = nullptr;

    if (!m_font.loadFromFile("include/Minecraft.ttf"))
        std::cout << "CAN'T LOAD FONT FILE!\n";
    m_text.setFont(m_font);
    m_fps.setFont(m_font);
    particles.reserve(50000);

    canDraw.store(false);
    isDrawing.store(false);

    Game::SetWindow(window);
    Game::InitPhysicsThread(collisionCheck, particles, this);

    particle_buffer1 = sf::VertexArray(sf::Quads);
    RenderingThread = std::thread(&Window::Render, std::ref(particles), std::ref(particle_buffer1), 1, std::ref(canDraw), std::ref(isDrawing));
    RenderingThread.detach();

    /*ArrayUpdater = std::thread(&Window::UpdateArrays, collisionCheck, std::ref(particles));
    ArrayUpdater.detach();*/

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
    float tmpTime = 0;
    m_text.setCharacterSize(14);
    m_fps.setCharacterSize(14);
    m_fps.setPosition(sf::Vector2f(0, 15));

    while (window->isOpen())
    {
        oldTime = newTime;
        newTime = time.getElapsedTime().asMicroseconds();
        CheckEvents();
        std::string text = std::to_string(particles.size());
        m_text.setString(text);

        if (time.getElapsedTime().asMilliseconds() > tmpTime)
        {
            m_fps.setString(std::to_string(DeltaTime));
            tmpTime = time.getElapsedTime().asMilliseconds() + 100;
        }

        if (particle_buffer1.getVertexCount() > 3 && canDraw.load())
        {
            isDrawing.store(true);
            window->clear();
            window->draw(m_text);
            window->draw(m_fps);
            window->draw(particle_buffer1);
            isDrawing.store(false);
        }
        
        window->display();
        DeltaTime =  1 / ((newTime - oldTime) / 1000000);
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
                //particle->mtx.lock();
                int screenPos = particle->screenGridPos;
                Vector2 roundedPos = Vector2::roundVector(particle->m_pos, 4);
                //particle->mtx.unlock();

                sf::Vector2f partPos(roundedPos.x, roundedPos.y);

                particle_buffer.append(sf::Vertex(sf::Vector2f(partPos.x, partPos.y), sf::Color::Magenta));
                particle_buffer.append(sf::Vertex(sf::Vector2f(partPos.x  + 4, partPos.y), sf::Color::Cyan));
                particle_buffer.append(sf::Vertex(sf::Vector2f(partPos.x + 4, partPos.y + 4), sf::Color::Cyan));
                particle_buffer.append(sf::Vertex(sf::Vector2f(partPos.x, partPos.y + 4), sf::Color::Magenta));
            }
            canDraw.store(true);
        }
        
        //Clamp de thread refresh rate by 144FPS, avoinding the thread to use all the CPU Power trying to refresh the buffer an insane amount of times per frame
        std::this_thread::sleep_for(std::chrono::microseconds(6900));
    }
}

void Window::UpdateArrays(ArrData* arr, std::vector<Particle*>& particles)
{
    for (int i = 0; i < 40000; ++i)
        arr[i].part = nullptr;

    for (Particle* particle : particles)
    {
        Vector2 pos = Vector2::roundVector(particle->m_pos, 4);
        int posX = pos.x / 4;
        int posY = pos.y / 4;

        //arr[posY * 200 + posX].mtx.lock();
        arr[posY * 200 + posX].part = particle;
        //arr[posY * 200 + posX].mtx.unlock();

        //std::cout << "Col pos:" << posX << " / " << posY << "\n";
    }

}