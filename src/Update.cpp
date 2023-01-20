#include "Engine.h"
#include "Function.h"



static const char OUTPUT_PATH[255] = "resources/out.txt";

using namespace sf;

const double friction = 0.5;



// запись в файл
void Engine::saveToFile() {
    // открываем поток данных для записи в файл
    std::ofstream output(OUTPUT_PATH);

    // выводим в несколько строк информацию о предыдущем столкновению
    output << "||||||||||||||||||||||||||||||||||||||||||||||" << std::endl;
    output << m_Ball.last_impact.center_position.x << " " << m_Ball.last_impact.center_position.y <<  " Вектор на центр" << std::endl;
    output << m_Ball.last_impact.impact_position.x << " " << m_Ball.last_impact.impact_position.y << " Вектор на точку столкновения" << std::endl;
    output << m_Ball.last_impact.speed.first.x << " " << m_Ball.last_impact.speed.first.y << " Начальная скорость" << std::endl;
    output << m_Ball.last_impact.speed.second.x << " " << m_Ball.last_impact.speed.second.y << " Конечная скорость" << std::endl;
    output << m_Ball.last_impact.angle << " Угол на точку столкновения" << std::endl;
    output << m_Ball.last_impact.round_angle << " Угол проворота кольца" << std::endl;
    output << m_Ball.last_impact.ans << " Ожидаемый номер сектора попадания" << std::endl << std::endl;
    output << m_Ball.last_impact.time_after_impact << " Время, прошедшее с предыдущего столкновения" << std::endl << std::endl;
    // закрываем
    output.close();
}

// работа с файлами
void Engine::ShowFiles() {
    // если не раскрыта панель `Files`
    if (!ImGui::CollapsingHeader("Сохранения"))
        // заканчиваем выполнение
        return;

    ImGui::PushID(0);
    // создаём кнопку сохранения
    if (ImGui::Button("Сохранить игру")) {
        // сохраняем задачу в файл
        saveToFile();
    }
    // восстанавливаем буфер id
    ImGui::PopID();

}

// если во всех целевых секторах стоит требуемое число игра завершается победой
bool Engine::checkWin()
{
    int ans = 0;
    for(int i = 0; i < m_Circle.size[m_Circle.type]; i++)
    {
        ans += m_Circle.round[i].isExecution();
    }
    return (ans == target_num);
}

void impact(Ball &m_Ball, Circle &m_Circle, float dtAsSeconds)
{
    m_Ball.speed = m_Ball.speed*m_Ball.k_energy/(m_Ball.k_energy - m_Ball.w_speed*m_Ball.w_speed*m_Ball.radius*2/5);
    if(dtAsSeconds > friction)
    {
        m_Ball.w_speed = m_Circle.w_speed;
    }
    else{
        m_Ball.w_speed += (m_Circle.w_speed - m_Ball.w_speed)*dtAsSeconds/friction;
    }
    m_Ball.speed = m_Ball.speed/m_Ball.k_energy*(m_Ball.k_energy - m_Ball.w_speed*m_Ball.w_speed*m_Ball.radius*2/5);
    Vector2f d = m_Ball.position - m_Circle.centerPosition;
    d = rotation(d, -m_Circle.w_speed*dtAsSeconds/2);
    float d_l = sqrt(d.x*d.x + d.y*d.y);
    d *= 2*scalar(d/d_l,m_Ball.speed)/d_l;
    m_Ball.speed = m_Ball.speed - d;
    m_Ball.last_impact.time_after_impact = 0;
}

void Engine::update(float dtAsSeconds)
{
    m_Ball.update(dtAsSeconds);
    m_Circle.update(dtAsSeconds);
    m_Ball.last_impact.impact_position = rotation(m_Ball.last_impact.impact_position,dtAsSeconds*m_Circle.w_speed*M_PI/180);
    if(m_Ball.checkPosition(m_Circle) && m_Ball.last_impact.time_after_impact > 0.1)
    {
        m_Ball.last_impact.center_position = m_Ball.position;
        m_Ball.last_impact.speed.first = m_Ball.speed;
        int i = m_Ball.checkSegment(m_Circle);
        if(i == -1)
        {
            endEvent(1);
        }
        int ans = (m_Ball.condition + m_Circle.round[i].getCondition()) % 6;
        m_Circle.round[i].update(ans);
        m_Circle.round[i].checkExecution(target);
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
