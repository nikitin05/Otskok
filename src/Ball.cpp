//
// Created by nikitinf05 on 13.11.2022.
//

#include "Ball.h"

Ball::Ball()
{
    speed.x = 70;
    speed.y = 0;
    w_speed = 0.0;
    k_energy = speed.x*speed.x + speed.y*speed.y;

    position.x = 300;
    position.y = 250;

    condition = 0;

    time_after_impact = 0.1;
}

Sprite Ball::getSprite()
{
    return sprite;
}

void Ball::setSprite(Texture &texture)
{
    sprite.setTexture(texture);

    sprite.setTextureRect(IntRect(2*condition*radius,0,2*radius,2*radius));

    sprite.setOrigin(radius, radius);
}

void Ball::update(int condition)
{
    this->condition = condition;
    sprite.setTextureRect(IntRect(2*condition*radius,0,2*radius,2*radius));
}

bool Ball::checkPosition(Circle circle)
{
    long double r = (position.x-circle.centerPosition.x)*(position.x-circle.centerPosition.x) + (position.y-circle.centerPosition.y)*(position.y-circle.centerPosition.y);
    if(((circle.radius - circle.width - radius)*(circle.radius - circle.width - radius) - r) < 0)
    {
        return true;
    }
    return false;
}

int Ball::checkSegment(Circle circle)
{
    Vector2f delta = position - circle.centerPosition;
    double angle = 180/M_PI*acos(delta.x/sqrt(delta.x*delta.x + delta.y*delta.y));
    if(position.y < circle.centerPosition.y)
    {
        angle = 360 - angle;
    }
    angle -= circle.round[0].angle;
    int ans = angle/22.5;
    ans = ans % 16;
    if(ans < 0)
    {
        ans += 16;
    }
    return ans;
}

void impact(Circle circle)
{

}

void Ball::update(float elapsedTime)
{
    time_after_impact += elapsedTime;
    sprite.rotate(w_speed*elapsedTime);
    position += speed*elapsedTime;
    sprite.setPosition(position);

}


