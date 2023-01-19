#include "Engine.h"

void Engine::input()
{
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        m_Circle.w_speed -= 0.25;
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
    {
         m_Circle.w_speed += 0.25;
    }
    if(Keyboard::isKeyPressed(Keyboard::Escape))
    {
        condition_game = game_Close;
    }
}

