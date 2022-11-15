#include "Engine.h"
#include "Function.h"



static const char OUTPUT_PATH[255] = "resources/out.txt";

using namespace sf;

const double friction = 0.5;

float scalar(Vector2f a, Vector2f b)
{
    return a.x*b.x + a.y*b.y;
}

// запись в файл
void Engine::saveToFile() {
    // открываем поток данных для записи в файл
    std::ofstream output(OUTPUT_PATH);

    // выводим через пробел построчно: x-координату, y-координату и номер множества
    output << "||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
    output << m_Ball.last_impact.center_position.x << " " << m_Ball.last_impact.center_position.y <<  " Вектор на центр" << std::endl;
    output << m_Ball.last_impact.impact_position.x << " " << m_Ball.last_impact.impact_position.y << " Вектор на точку столкновения" << std::endl;
    output << m_Ball.last_impact.speed.first.x << " " << m_Ball.last_impact.speed.first.y << " Начальная скорость" << std::endl;
    output << m_Ball.last_impact.speed.second.x << " " << m_Ball.last_impact.speed.second.y << " Конечная скорость" << std::endl;
    output << m_Ball.last_impact.angle << " Угол на точку столкновения" << std::endl;
    output << m_Ball.last_impact.round_angle << " Угол проворота кольца" << std::endl;
    output << m_Ball.last_impact.ans << " Ожидаемый номер сектора попадания" << std::endl << std::endl;
    // закрываем
    output.close();
}

// работа с файлами
void Engine::ShowFiles() {
    // если не раскрыта панель `Files`
    if (!ImGui::CollapsingHeader("Files"))
        // заканчиваем выполнение
        return;

    ImGui::PushID(0);
    // создаём кнопку сохранения
    if (ImGui::Button("Save")) {
        // сохраняем задачу в файл
        saveToFile();
    }
    // восстанавливаем буфер id
    ImGui::PopID();

}


bool Engine::checkWin()
{
    bool ans = true;
    for(int i = 0; i < 16; i++)
    {
        if(m_Circle.round[i].target == 1 && m_Circle.round[i].condition != target)
        {
            ans = false;
        }
    }
    return ans;
}

void impact(Ball &m_Ball, Circle &m_Circle, float dtAsSeconds)
{
    if(dtAsSeconds > friction)
    {
        m_Ball.w_speed = m_Circle.w_speed;
    }
    else{
        m_Ball.w_speed += (m_Circle.w_speed - m_Ball.w_speed)*dtAsSeconds/friction;
    }
    Vector2f d = m_Ball.position - m_Circle.centerPosition;
    d = rotation(d, -m_Circle.w_speed*dtAsSeconds/2);
    float d_l = sqrt(d.x*d.x + d.y*d.y);
    float speed_n = scalar(d,m_Ball.speed) / d_l;
    float speed_t = sqrt(scalar(m_Ball.speed, m_Ball.speed) - speed_n*speed_n);
    float speed_t_new = m_Ball.k_energy - speed_n*speed_n - m_Ball.w_speed*m_Ball.w_speed*m_Ball.radius*2/5;
    if(speed_t_new < 0)
    {
        speed_t_new = 0;
    }
    speed_t_new = sqrt(speed_t_new);
    d = - d * speed_n/d_l;
    m_Ball.speed = (d*(speed_t + speed_t_new) + speed_t_new*m_Ball.speed)/speed_t;
    m_Ball.time_after_impact = -0.25;
}

void Engine::update(float dtAsSeconds)
{
    m_Ball.update(dtAsSeconds);
    m_Circle.update(dtAsSeconds);
    m_Ball.last_impact.impact_position = rotation(m_Ball.last_impact.impact_position,dtAsSeconds*m_Circle.w_speed*M_PI/180);
    if(m_Ball.checkPosition(m_Circle) && m_Ball.time_after_impact > 0)
    {
        if(m_Ball.time_after_impact < 0.08)
        {
            endEvent(1);
        }
        m_Ball.last_impact.center_position = m_Ball.position;
        m_Ball.last_impact.speed.first = m_Ball.speed;
        int i = m_Ball.checkSegment(m_Circle);
        int ans = (m_Ball.condition + m_Circle.round[i].condition) % 6;
        m_Circle.round[i].update(ans);
        m_Ball.update(ans);
        impact(m_Ball, m_Circle, dtAsSeconds);
        m_Ball.last_impact.speed.second = m_Ball.speed;
        if(checkWin())
        {
            endEvent(2);
        }
    }
}
