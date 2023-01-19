//
// Created by nikitinf05 on 13.11.2022.
//

#include "Circle.h"

Segment::Segment()
{
    condition = 0;
    target = true;

    angle = 0.0;
}

Sprite Segment::getSprite()
{
    return sprite;
}

void Segment::setPosition(int type, double angle, Vector2f position, Texture &texture)
{
    this->type = type;
    sprite.rotate(-this->angle);
    this->angle = angle;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(texturePosition[type].x+width[type]*condition,texturePosition[type].y+height[type]*target,width[type],height[type]));
    sprite.setOrigin(spriteOrigin[type]);
    sprite.rotate(angle);
    sprite.setPosition(position);
}

void Segment::update(double angle)
{
    this->angle += angle;
    sprite.rotate(angle);
}

void Segment::update(int condition)
{
    this->condition = condition;
    sprite.setTextureRect(IntRect(texturePosition[type].x+width[type]*condition,texturePosition[type].y+height[type]*target,width[type],height[type]));
}

void Segment::update(bool target) {
    this->target = target;
}

bool Segment::checkExecution(int tar) {
    if(target == 1 && condition != tar)
    {
        return false;
    }
    return true;
}

int Segment::getCondition() {
    return condition;
}

double Segment::getAngle() {
    return angle;
}


Circle::Circle()
{
    w_speed = 0.0;

    centerPosition.x = 400;
    centerPosition.y = 400;

    segment.loadFromFile("resources/segment.png");
    segment.setSmooth(true);

    radius = 324;
}

void Circle::update(float elapsedTime)
{
    for(int i = 0;i < size[type]; i++)
    {
        round[i].update(elapsedTime*w_speed);
    }
}

