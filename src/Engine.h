//
// Created by nikitinf05 on 13.11.2022.
//

#ifndef OTSKOK_ENGINE_H
#define OTSKOK_ENGINE_H



#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Circle.h"

using namespace sf;

class Engine
{
private:

    RenderWindow m_Window;

    Sprite m_BackgroundSprite;
    Texture m_BackgroundTexture;
    Texture ball;
    Font font;

    Ball m_Ball;
    Circle m_Circle;

    int target;
    Text target_text;

    bool checkWin();

    void input();
    void update(float dtAsSeconds);
    void draw();
    void endEvent(int type_of_damage);

public:

    Engine();
    void start();
};


#endif //OTSKOK_ENGINE_H
