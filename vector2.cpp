#include "Vector2.hpp"

Vector2::Vector2()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
    Vector2 returnVector(v1.x + v2.x, v1.y + v2.y);
    return returnVector;
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
    Vector2 returnVector(v1.x - v2.x, v1.y - v2.y);
    return returnVector;
}

Vector2 operator*(const Vector2& v1, const Vector2& v2)
{
    Vector2 returnVector(v1.x * v2.x, v1.y * v2.y);
    return returnVector;
}

Vector2 operator*(const Vector2& v1, const float scalar)
{
    Vector2 returnVector(v1.x * scalar, v1.y * scalar);
    return returnVector;
}

Vector2 operator/(const Vector2& v1, const Vector2& v2)
{
    Vector2 returnVector(v1.x / v2.x, v1.y / v2.y);
    return returnVector;
}

Vector2 operator/(const Vector2& v1, const float scalar)
{
    Vector2 returnVector(v1.x / scalar, v1.y / scalar);
    return returnVector;
}

Vector2& Vector2::operator+=(const Vector2& v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& v)
{
    this->x *= v.x;
    this->y *= v.y;
    return *this;
}

Vector2& Vector2::operator*=(const float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}


Vector2& Vector2::operator/=(const Vector2& v)
{
    this->x /= v.x;
    this->y /= v.y;
    return *this;
}

Vector2& Vector2::operator/=(const float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2& vec)
{
    return stream << "(" << vec.x << "," << vec.y << ")";
}

float Vector2::mag()
{
    return sqrtf(this->x * this->x + this->y * this->y);
}

void Vector2::normalize()
{
    float mag = this->mag();
    this->x /= mag;
    this->y /= mag;
}

float Vector2::angleBetween(Vector2 otherV)
{
    return 180 / 3.141592653 * (atan2f(otherV.y, otherV.x) - atan2f(this->y, this->x));
}

float Vector2::distance(Vector2 otherV)
{
    return sqrt(powf(this->x - otherV.x, 2) + powf(this->y - otherV.y, 2));
}