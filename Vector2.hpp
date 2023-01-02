#pragma once
#include <iostream>
#include <cmath>

class Vector2
{
private:
    Vector2& add(const Vector2& v);
    Vector2& subtract(const Vector2& v);
    Vector2& multiply(const Vector2& v);
    Vector2& divide(const Vector2& v);

public:
    float x;
    float y;

    Vector2();
    Vector2(float x, float y);
    float mag();
    float distance(Vector2 otherV);
    void normalize();
    float angleBetween(Vector2 otherV);
    friend Vector2& operator+(Vector2& v1, const Vector2& v2);
    friend Vector2& operator-(Vector2& v1, const Vector2& v2);
    friend Vector2& operator*(Vector2& v1, const Vector2& v2);
    friend Vector2& operator/(Vector2& v1, const Vector2& v2);

    Vector2& operator+=(const Vector2& v);
    Vector2& operator-=(const Vector2& v);
    Vector2& operator*=(const Vector2& v);
    Vector2& operator/=(const Vector2& v);

    friend std::ostream& operator<<(std::ostream& stream, const Vector2& vec);
};