#pragma once
#include <cmath>

class Vector2
{
public:
    Vector2() 
    { 
        x = 0; y = 0; 
    }
    Vector2(float px, float py)
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
    static Vector2 roundVector(Vector2 numToRound, float multiple)
    {
        float x;
        float y;

        x = round(numToRound.x / multiple) * multiple;
        y = round(numToRound.y / multiple) * multiple;

        return Vector2(x, y);
    }
    static Vector2 Add(Vector2& p_vec, Vector2& p_vec2)
    {
        Vector2 result;
        result.x = p_vec.x + p_vec2.x;
        result.y = p_vec.y + p_vec2.y;
        return result;
    }

    float GetMagnitude() { return sqrt(pow(x, 2) + pow(y, 2)); }
    Vector2 operator +=(const Vector2& p_vec)
    {
        return Vector2(this->x + p_vec.x, this->y + p_vec.y);
    }
};