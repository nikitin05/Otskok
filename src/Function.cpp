#include "function.h"



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

float max(float a, float b)
{
    if(a > b)
        return a;
    return b;
}