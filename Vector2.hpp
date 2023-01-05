#pragma once
#include <iostream>
#include <cmath>

class Vector2
{
public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);
    float mag();
    float distance(Vector2 otherV);
    void normalize();
    float angleBetween(Vector2 otherV);
    friend Vector2 operator+(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator-(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator*(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator*(const Vector2& v1, const float scalar);
    friend Vector2 operator/(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator/(const Vector2& v1, const float scalar);


    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);
    Vector2& operator*=(const Vector2& v);
    Vector2& operator*=(const float scalar);
    Vector2& operator/=(const Vector2& v);
    Vector2& operator/=(const float scalar);


    friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);
};