//
// Created by nikitinf05 on 13.11.2022.
//

#include "Engine.h"
#include "thread"


Engine::Engine()
{
    Resolution = Vector2f(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
    event_resolution = Vector2f(0,0);

    m_Window.create(VideoMode(Resolution.x, Resolution.y), "Otskok", Style::Fullscreen);

    m_Window.setFramerateLimit(60);
    ImGui::SFML::Init(m_Window);

    m_BackgroundTexture.loadFromFile("resources/background.png");
    m_BackgroundSprite.setTexture(m_BackgroundTexture);
    ball.loadFromFile("resources/ball.png");

    // загрузка шрифта для кириллицы
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    //io.Fonts->AddFontDefault();

    // нужно добавить файл со шрифтами и указать к нему путь
    io.Fonts->AddFontFromFileTTF("resources/arial.ttf", 16.f, NULL,
                                 ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    font.loadFromFile("resources/arial.ttf");

    // фиксирование изменений
    ImGui::SFML::UpdateFontTexture();

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

    event_id = 3;
    game_speed = 146;
}

void Engine::start()
{
    while (m_Window.isOpen())
    {
        studing();

        sf::Event sf_event;
        while (m_Window.pollEvent(sf_event))
        {
            ImGui::SFML::ProcessEvent(sf_event);
            if (sf_event.type == sf::Event::Closed)
                m_Window.close();
        }

        Time dt = clock.restart();
        dt = dt*(game_speed*0.01f);
        float dtAsSeconds = dt.asSeconds();
        ImGui::SFML::Update(m_Window, dt);
        if(condition_game == game_Open) {
            input();
            update(dtAsSeconds);
        }



        ImGui::Begin("Меню");

        ShowFiles();

        const char* condition_game_name = (condition_game >= 0 && condition_game < 2) ? game_names[condition_game] : "Unknown";
        ImGui::SliderInt("Состояние игры", &condition_game, 0, 1, condition_game_name);

        const char* condition_physicOverlay_name = (condition_physicOverlay >= 0 && condition_physicOverlay < 2) ? physicOverlay_names[condition_physicOverlay] : "Unknown";
        ImGui::SliderInt("Физическая визуализация", &condition_physicOverlay, 0, 1, condition_physicOverlay_name);
        ImGui::DragInt("Скорость игры (%)", &game_speed, 1, 1, 200, "%d%%", ImGuiSliderFlags_AlwaysClamp);

        if(ImGui::Button("Выйти на рабочий стол"))
        {
            m_Window.close();
            break;
        }

        ImGui::End();

        ImGui::ShowDemoWindow();

        event(event_id);

        draw();
    }
    ImGui::SFML::Shutdown();
}

void Engine::studing()
{
    if(event_id == 3 || event_id == 4 || event_id == 5)
    {
        m_Ball.speed = Vector2f (0,0);
        event_id = 3;
        if(game_speed == 100)
        {
            event_id = 4;
            if(condition_physicOverlay == physicOverlay_Open)
            {
                event_id = 5;
                if(condition_game == game_Open)
                {
                    event_id = 0;
                    m_Ball.speed = Vector2f (100,0);
                }
            }
        }
    }
    else if(m_Ball.last_impact.impact_position != Vector2f(0,0) && event_id != 6)
    {
        event_id = 6;
        condition_game = game_Close;
    }
}