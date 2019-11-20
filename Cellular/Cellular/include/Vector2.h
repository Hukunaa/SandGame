#pragma once
#include <cmath>

class Vector2
{
public:
    Vector2() 
    { 
        x = 0; y = 0; 
    }
    Vector2(int px, int py)
    {
        x = px; y = py;
    }
    ~Vector2() {};

    float x;
    float y;

    static Vector2 Zero()
    {
        return Vector2(0, 0);
    }
    static Vector2 roundUp(Vector2 numToRound, float multiple)
    {
        float x;
        float y;

        //X
        if (multiple == 0)
            x = numToRound.x;

        float absolute = abs(numToRound.x);
        float remainderX = (int)absolute % (int)multiple;
        if (remainderX == 0)
            x = numToRound.x;

        if (numToRound.x < 0)
            x = -(absolute - remainderX);
        else
            x = numToRound.x + multiple - remainderX;

        //Y
        if (multiple == 0)
            y = numToRound.y;

        float absoluteY = abs(numToRound.y);
        float remainderY = (int)absoluteY % (int)multiple;

        if (remainderY == 0)
            y = numToRound.y;

        if (numToRound.y < 0)
            y = -(absoluteY - remainderY);
        else
            y = numToRound.y + multiple - remainderY;
        return Vector2(x, y);
    }
    static Vector2 Add(Vector2& p_vec, Vector2& p_vec2)
    {
        Vector2 result;
        result.x = p_vec.x + p_vec2.x;
        result.y = p_vec.y + p_vec2.y;
        return result;
    }

    Vector2 operator +=(const Vector2& p_vec)
    {
        return Vector2(this->x + p_vec.x, this->y + p_vec.y);
    }
};