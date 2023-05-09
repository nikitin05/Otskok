#include "Engine.h"
#include "Function.h"
#include "iostream"
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
            m_Ball.last_impact.center_position,
            m_Ball.last_impact.center_position + m_Ball.last_impact.speed.first,
            ImColor(200,100,100),
            5
            );
    pDrawList->AddLine(
            m_Ball.last_impact.center_position,
            m_Ball.last_impact.center_position + m_Ball.last_impact.speed.second,
            ImColor(100,200,100),
            5
    );
    pDrawList->AddCircleFilled(
            m_Circle.centerPosition + m_Ball.last_impact.impact_position,
            10,
            ImColor(100,100,200)
            );
    ImGui::End();
}

void Engine::draw()
{
    m_Window.clear(Color::White);

    if(condition_physicOverlay == physicOverlay_Open)
    {
        impact_draw();
    }

    m_Window.draw(m_BackgroundSprite);
    m_Window.draw(m_Ball.getSprite());
    for(int i = 0; i < m_Circle.size[m_Circle.type]; i++)
    {
        m_Window.draw(m_Circle.round[i].getSprite());
    }
    m_Window.draw(target_text);
    m_Window.draw(target_num_text);
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
    text.getString();
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

void Engine::event(int event_id)
{
    //сразу завершаем функцию, если ничего выводить не нужно
    if(event_id == 0)
    {
        return;
    }

    //задаем ширину выводимого текста
    const float wrap_width = 200.0;
    //задаем верхний-левый угол окна события
    Vector2f position = Resolution*0.5f;

    //выбираем текст в зависимости от типа события
    std::string text;
    switch(event_id){
        case 1:
            text = u8"Шарик сломался из-за продолжительного соприкосновения с поверхностью";
            break;
        case 2:
            text = u8"ВЫ ПОБЕДИЛИ!!!";
            break;
        case 3:
            text = u8"Установите скорость игры в меню на 100%";
            break;
        case 4:
            text = u8"Включите физическую визуализацию, сдвинув соответственный тумблер в меню. Она позволит вам на первых порах лучше понимать логику отскоков";
            break;
        case 5:
            text = u8"Снимите игру с паузы, сдвинув соответственный тумблер в меню";
            break;
        case 6:
            text = u8"Только что произошло самое главное событие в игре - столкновение шарика с вращающимся ободком. В результате направление и скорость движения "
                   "шарика изменились(физическая визуализация показывает вам как) и числа, записанные в секторе, с которым столкнулся шарик, и в нем самом изменились "
                   "и стали равны сумме изначальных по модулю 6. Число, стоящее в шарике или секторе визуализируется количеством точек в нем и принимает значения от 0 до 5. "
                   "Для продолжения игры и закрытия окна сдвиньте тумблер в меню. ";
            break;
        case 7:
            text = u8"";
            break;
    }

    // задаём левый верхний край невидимого окна
    ImGui::SetNextWindowPos(position);
    // задаём правый нижний край невидимого окна
    ImGui::SetNextWindowSize(event_resolution+Vector2f(10,10));
    //создаем окно
    ImGui::Begin("text", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                 ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs );

    //задаем ограничение на ширину текста
    ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
    //пишем текст
    ImGui::Text(text.c_str(),wrap_width);

    //перерасчет ширины окна, чтобы в нее влезал текст
    event_resolution = ImGui::GetItemRectMax();
    event_resolution -= position;

    //рисуем рамочку вокруг текста
    auto draw_list = ImGui::GetWindowDrawList();
    draw_list->AddRect(ImGui::GetItemRectMin(), event_resolution + position, IM_COL32(255, 255, 0, 255));
    //отменяем ограничение на ширине текста
    ImGui::PopTextWrapPos();

    //закрываем окно
    ImGui::End();
}
