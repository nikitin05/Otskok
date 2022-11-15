#include "Engine.h"
//#include "iostream"
#include "thread"

void Engine::impact_draw()
{
    // задаём левый верхний край невидимого окна
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    // задаём правый нижний край невидимого окна
    ImGui::SetNextWindowSize(Resolution);
    // создаём невидимое окно
    ImGui::Begin("Last_Impact", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
    // получаем список примитивов, которые будут нарисованы
    auto pDrawList = ImGui::GetWindowDrawList();

    pDrawList->AddLine(
            m_Ball.last_impact.position.first,
            m_Ball.last_impact.position.first + m_Ball.last_impact.speed.first,
            ImColor(200,100,100),
            5
            );
    pDrawList->AddLine(
            m_Ball.last_impact.position.first,
            m_Ball.last_impact.position.first + m_Ball.last_impact.speed.second,
            ImColor(100,200,100),
            5
    );
    pDrawList->AddCircleFilled(
            m_Circle.centerPosition + m_Ball.last_impact.position.second,
            10,
            ImColor(100,100,200)
            );

    ImGui::End();
}

void Engine::draw()
{
    impact_draw();
    m_Window.clear(Color::White);

    m_Window.draw(m_BackgroundSprite);
    m_Window.draw(m_Ball.getSprite());
    for(int i = 0; i < 16; i++)
    {
        m_Window.draw(m_Circle.round[i].getSprite());
    }
    m_Window.draw(target_text);
    ImGui::SFML::Render(m_Window);
    m_Window.display();
}

void Engine::endEvent(int type_of_end)
{
    m_Window.clear(Color::White);
    Text text;
    std::wstring s = L"";
    switch(type_of_end){
case 1:
    s += L"Шарик сломался из-за продолжительного соприкосновения с поверхностью. ";
    break;
case 2:
     s += L"ВЫ ПОБЕДИЛИ!!! ";
    break;
    }
    s += L"Для выхода из игры нажмите Esc";
    Vector2f position;
    position.x = 300;
    position.y = 0;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setString(s);
    text.setFillColor(Color::Black);
    text.setStyle(sf::Text::Bold);
    m_Window.draw(text);
    m_Window.display();
    while(!Keyboard::isKeyPressed(Keyboard::Escape))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    m_Window.close();
}
