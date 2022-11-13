#include "Engine.h"
//#include "iostream"
#include "thread"

void Engine::draw()
{
    m_Window.clear(Color::White);

    m_Window.draw(m_BackgroundSprite);
    m_Window.draw(m_Ball.getSprite());
    for(int i = 0; i < 16; i++)
    {
        m_Window.draw(m_Circle.round[i].getSprite());
    }
    m_Window.draw(target_text);
    m_Window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
