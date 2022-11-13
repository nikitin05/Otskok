//
// Created by nikitinf05 on 13.11.2022.
//

#include "Engine.h"
#include "thread"


//const double fps = 0.01;

Engine::Engine()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(resolution.x, resolution.y), "Simple Game Engine", Style::Fullscreen);

    m_BackgroundTexture.loadFromFile("resources/background.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
    ball.loadFromFile("resources/ball.png");
    font.loadFromFile("resources/arial.ttf");
    m_Ball.setSprite(ball);
    for(int i = 0; i < 16; i++)
    {
        m_Circle.round[i].target = rand() % 2;
        m_Circle.round[i].update(rand() % 6);
    }

    target = rand() % 6;
    target_text.setFont(font);
    target_text.setCharacterSize(24);
    target_text.setString(std::to_string(target));
    target_text.setFillColor(Color::Black);
    target_text.setStyle(sf::Text::Bold);
    Vector2f position;
    position.x = 900;
    position.y = 300;
    target_text.setPosition(position);
}

void Engine::start()
{
    Clock clock;
    while (m_Window.isOpen())
    {
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();
        input();
        update(dtAsSeconds);
        draw();
        /*dt =  clock.getElapsedTime();
        dtAsSeconds += dt.asSeconds();
        if(dtAsSeconds < fps)
        {
            int sleep = fps - dtAsSeconds;
            std::this_thread::sleep_for(std::chrono::seconds(sleep));
            Time dt = clock.restart();
        }*/
        sf::Event event;
        while (m_Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_Window.close();
        }
    }
}

