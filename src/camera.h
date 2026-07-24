#pragma once

#include "geometry.h"

#include <raylib.h>

class ViewCamera
{
public:
    ViewCamera(geom::Vector2 position, float angle, float fov);

    void update(float delta_time);

    geom::Vector2 getPosition() const;
    float getAngle() const;
    float getFov() const;

private:
    geom::Vector2 position_{};
    float angle_{};
    float fov_{};
    float move_speed_{ 220.0F };
    float strafe_speed_{ 180.0F };
    float turn_speed_{ 2.6F };
};
