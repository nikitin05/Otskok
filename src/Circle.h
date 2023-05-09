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

    void setGameTargetCondition(int game_target_condition);

    void setPosition(int type, double angle, Vector2f position, Texture &texture);

    void update(double angle);
    void update(int condition);
    void update(bool target);

    void checkExecution(int tar);

    bool isExecution();

    int getCondition();

    double getAngle();

private:
    Sprite sprite;

    Texture texture;

    int type;

    const int width[2] = {90,71};
    const int height[2] = {190,142};
    const Vector2f texturePosition[2] = {Vector2f(426,0),Vector2f(0,0)};
    const Vector2f spriteOrigin[2] = {Vector2f(-234.0,10.0),Vector2f(-260.0,10.0)};

    int condition;
    bool target;
    bool game_target_condition;
    bool is_execution;

    double angle;
};

class Circle
{
public:
    Circle();

    void update(float elapsedTime);

    double w_speed;

    int width = 40;

    int radius;

    Vector2f centerPosition;

    Segment round[16];

    Texture segment;

    int type;
    int size[2] = {12,16};
};


#endif //OTSKOK_CIRCLE_H
