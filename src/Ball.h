//
// Created by nikitinf05 on 13.11.2022.
//

#ifndef OTSKOK_BALL_H
#define OTSKOK_BALL_H


#include <SFML/Graphics.hpp>
#include "Circle.h"


struct event_impact
{
    std::pair<Vector2f, Vector2f> position;
    std::pair<Vector2f, Vector2f> speed;
    event_impact(){
        position.first = Vector2f (0,0);
        position.second = Vector2f (0,0);
        speed.first = Vector2f (0,0);
        speed.second = Vector2f (0,0);
    }
};

using namespace sf;

class Ball
{
private:

    Sprite sprite;

    Texture texture;

public:
    event_impact last_impact;

    Vector2f position;

    Vector2f speed;
    double w_speed;
    long double k_energy;
    double time_after_impact;

    Ball();

    Sprite getSprite();
    void setSprite(Texture &texture);

    int radius = 30;

    int condition;

    bool checkPosition(Circle circle);

    int checkSegment(Circle circle);

    void update(float elapsedTime);

    void update(int conidition);
};


#endif //OTSKOK_BALL_H
