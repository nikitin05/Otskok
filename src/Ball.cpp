//
// Created by nikitinf05 on 13.11.2022.
//

#include "Ball.h"
#include "Function.h"



Ball::Ball()
{
    speed.x = 70;
    speed.y = 0;
    w_speed = 0.0;
    k_energy = speed.x*speed.x + speed.y*speed.y;

    position.x = 300;
    position.y = 250;

    condition = 0;

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
    last_impact.impact_position = Vector2f (circle.radius - circle.width,0);
    last_impact.impact_position = rotation(last_impact.impact_position, angle*M_PI/180);
    if(abs(last_impact.angle - angle) < 10.0)
    {
        return -1;
    }
    last_impact.angle = angle;
    angle -= circle.round[0].getAngle();
    last_impact.round_angle = circle.round[0].getAngle();
    while(angle < 0)
    {
        angle += 360;
    }
    int ans = angle/360.0*circle.size[circle.type];
    ans = ans % circle.size[circle.type];
    last_impact.ans = ans;
    return ans;
}

void Ball::update(float elapsedTime)
{
    last_impact.time_after_impact += elapsedTime;
    sprite.rotate(w_speed*elapsedTime);
    position += speed*elapsedTime;
    sprite.setPosition(position);

}


