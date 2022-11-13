//
// Created by nikitinf05 on 13.11.2022.
//

#ifndef OTSKOK_CIRCLE_H
#define OTSKOK_CIRCLE_H


#include <SFML/Graphics.hpp>
#include "cmath"
#include "iostream"
#include "thread"

using namespace sf;

struct Segment
{
public:
    Segment();

    Sprite getSprite();

    double angle;

    int radius;

    void setPosition(double angle, Vector2f position, Texture &texture);

    void update(double angle);

    void update(int condition);

    int condition;

    int target;

private:
    Sprite sprite;

    Texture texture;
};

class Circle
{
public:
    Circle();

    Sprite getSprite();

    void update(float elapsedTime);

    double w_speed;

    int width = 40;

    int radius;

    Vector2f centerPosition;

    Segment round[16];

    Texture segment;
};


#endif //OTSKOK_CIRCLE_H
