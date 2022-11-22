//
// Created by nikitinf05 on 13.11.2022.
//

#include "Engine.h"
#include "thread"


Engine::Engine()
{
    Resolution.x = VideoMode::getDesktopMode().width;
    Resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(Resolution.x, Resolution.y), "Otskok", Style::Fullscreen);

    m_Window.setFramerateLimit(60);
    ImGui::SFML::Init(m_Window);

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
        dt = dt*(game_speed*0.01f);
        float dtAsSeconds = dt.asSeconds();
        ImGui::SFML::Update(m_Window, dt);
        ImGui::Begin("Control");
        if(ImGui::Button("Pause"))
        {
            isPaused = true;
        }
        if(ImGui::Button("Play"))
        {
            isPaused = false;
        }
        if(ImGui::Button("Open Overlay"))
        {
           pOverlay_isOpen = true;
        }
        if(ImGui::Button("Close Overlay"))
        {
          pOverlay_isOpen = false;
         }
        ImGui::DragInt("drag int 0..100", &game_speed, 1, 0, 200, "%d%%", ImGuiSliderFlags_AlwaysClamp);
        if(game_speed == 0)
        {
            isPaused = true;
            game_speed = 1;
        }

        ImGui::End();
        if(!isPaused) {
            input();
            update(dtAsSeconds);
        }
        draw();
        sf::Event event;
        while (m_Window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                m_Window.close();
        }
    }
    ImGui::SFML::Shutdown();
}

