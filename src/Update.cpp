#include "Engine.h"




using namespace sf;

const double friction = 0.5;

Vector2f rotation(Vector2f a, double angle)
{
    Vector2f ans;
    ans.x = a.x*cos(angle) - a.y*sin(angle);
    ans.y = a.x*sin(angle) + a.y*cos(angle);
    return ans;
}

float scalar(Vector2f a, Vector2f b)
{
    return a.x*b.x + a.y*b.y;
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
    if(m_Ball.checkPosition(m_Circle) && m_Ball.time_after_impact > 0)
    {
        if(m_Ball.time_after_impact < 0.08)
        {
            endEvent(1);
        }
        int i = m_Ball.checkSegment(m_Circle);
        int ans = (m_Ball.condition + m_Circle.round[i].condition) % 6;
        m_Circle.round[i].update(ans);
        m_Ball.update(ans);
        impact(m_Ball, m_Circle, dtAsSeconds);
        if(checkWin())
        {
            endEvent(2);
        }
    }
}
