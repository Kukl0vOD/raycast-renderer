#pragma once

#include <raylib.h>

namespace geom
{
class Vector2
{
public:
    constexpr Vector2() = default;
    constexpr Vector2(float x_value, float y_value)
        : x(x_value)
        , y(y_value)
    {
    }

    constexpr operator ::Vector2() const
    {
        return { x, y };
    }

    Vector2& operator+=(Vector2 rhs);
    Vector2& operator-=(Vector2 rhs);
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);

    float x{};
    float y{};
};

struct CastRay
{
    Vector2 origin{};
    Vector2 direction{};
    float angle{};
};

struct RayHit
{
    bool hit{};
    Vector2 point{};
    float distance{};
    float ray_angle{};
    int wall_index{ -1 };
};

Vector2 operator+(Vector2 lhs, Vector2 rhs);
Vector2 operator-(Vector2 lhs, Vector2 rhs);
Vector2 operator-(Vector2 value);
Vector2 operator*(Vector2 value, float scalar);
Vector2 operator*(float scalar, Vector2 value);
Vector2 operator/(Vector2 value, float scalar);

float cross(Vector2 lhs, Vector2 rhs);
Vector2 fromAngle(float angle);
float length(Vector2 value);
Vector2 normalize(Vector2 value);
}
