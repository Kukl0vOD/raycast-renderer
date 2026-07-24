#include "camera.h"

ViewCamera::ViewCamera(geom::Vector2 position, float angle, float fov)
    : position_(position)
    , angle_(angle)
    , fov_(fov)
{
}

void ViewCamera::update(float delta_time)
{
    const geom::Vector2 forward = geom::fromAngle(angle_);
    const geom::Vector2 right{ -forward.y, forward.x };
    const float speed_multiplier = IsKeyDown(KEY_LEFT_SHIFT) ? 1.8F : 1.0F;

    if (IsKeyDown(KEY_LEFT))
    {
        angle_ -= turn_speed_ * delta_time;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        angle_ += turn_speed_ * delta_time;
    }

    if (IsKeyDown(KEY_W))
    {
        position_ += forward * (move_speed_ * speed_multiplier * delta_time);
    }

    if (IsKeyDown(KEY_S))
    {
        position_ -= forward * (move_speed_ * speed_multiplier * delta_time);
    }

    if (IsKeyDown(KEY_A))
    {
        position_ -= right * (strafe_speed_ * speed_multiplier * delta_time);
    }

    if (IsKeyDown(KEY_D))
    {
        position_ += right * (strafe_speed_ * speed_multiplier * delta_time);
    }
}

geom::Vector2 ViewCamera::getPosition() const
{
    return position_;
}

float ViewCamera::getAngle() const
{
    return angle_;
}

float ViewCamera::getFov() const
{
    return fov_;
}
