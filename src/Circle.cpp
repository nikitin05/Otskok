//
// Created by nikitinf05 on 13.11.2022.
//

#include "Circle.h"

Segment::Segment()
{
    condition = 0;
    target = 1;
    radius = 324;

    angle = 0.0;
}

Sprite Segment::getSprite()
{
    return sprite;
}

void Segment::setPosition(double angle, Vector2f position, Texture &texture)
{
    this->angle += angle;
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(condition*radius,136*target,radius,136));
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
    sprite.setTextureRect(IntRect(condition*radius,136*target,radius,136));
}

Circle::Circle()
{
    w_speed = 0.0;

    centerPosition.x = 400;
    centerPosition.y = 400;

    segment.loadFromFile("resources/segment.png");

    for(int i = 0; i < 16; i++)
    {
        round[i].setPosition(22.5 * i, centerPosition, segment);
    }

    radius = round[0].radius;
}

void Circle::update(float elapsedTime)
{
    for(int i = 0;i < 16; i++)
    {
        round[i].update(elapsedTime*w_speed);
    }
}

