#include "geometry.h"

#include <cmath>

namespace geom
{
Vector2& Vector2::operator+=(Vector2 rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector2& Vector2::operator-=(Vector2 rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2 operator+(Vector2 lhs, Vector2 rhs)
{
    lhs += rhs;
    return lhs;
}

Vector2 operator-(Vector2 lhs, Vector2 rhs)
{
    lhs -= rhs;
    return lhs;
}

Vector2 operator-(Vector2 value)
{
    return { -value.x, -value.y };
}

Vector2 operator*(Vector2 value, float scalar)
{
    value *= scalar;
    return value;
}

Vector2 operator*(float scalar, Vector2 value)
{
    return value * scalar;
}

Vector2 operator/(Vector2 value, float scalar)
{
    value /= scalar;
    return value;
}

float cross(Vector2 lhs, Vector2 rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

Vector2 fromAngle(float angle)
{
    return { std::cos(angle), std::sin(angle) };
}

float length(Vector2 value)
{
    return std::sqrt(value.x * value.x + value.y * value.y);
}

Vector2 normalize(Vector2 value)
{
    const float value_length = length(value);

    if (value_length == 0.0F)
    {
        return {};
    }

    return value / value_length;
}
}
