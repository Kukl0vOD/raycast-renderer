#include "raycaster.h"

#include <cmath>

namespace
{
constexpr float epsilon = 0.00001F;
}

Raycaster::Raycaster(int ray_count, float max_distance)
    : ray_count_(ray_count)
    , max_distance_(max_distance)
{
}

std::vector<geom::RayHit> Raycaster::cast(const ViewCamera& camera, const Scene& scene) const
{
    std::vector<geom::RayHit> hits;
    hits.reserve(ray_count_);

    const float angle_step = camera.getFov() / static_cast<float>(ray_count_);
    const float first_angle = camera.getAngle() - camera.getFov() * 0.5F;

    for (int i = 0; i < ray_count_; ++i)
    {
        const float ray_angle = first_angle + angle_step * (static_cast<float>(i) + 0.5F);
        const geom::CastRay ray{ camera.getPosition(), geom::fromAngle(ray_angle), ray_angle };
        hits.push_back(castRay(ray, scene));
    }

    return hits;
}

int Raycaster::rayCount() const
{
    return ray_count_;
}

geom::RayHit Raycaster::castRay(const geom::CastRay& ray, const Scene& scene) const
{
    geom::RayHit closest_hit{};
    closest_hit.distance = max_distance_;
    closest_hit.ray_angle = ray.angle;

    const auto& walls = scene.getWalls();
    for (int i = 0; i < static_cast<int>(walls.size()); ++i)
    {
        const geom::RayHit hit = intersectWall(ray, walls[i], i);

        if (hit.hit && hit.distance < closest_hit.distance)
        {
            closest_hit = hit;
        }
    }

    if (!closest_hit.hit)
    {
        closest_hit.point = ray.origin + ray.direction * max_distance_;
    }

    return closest_hit;
}

geom::RayHit Raycaster::intersectWall(const geom::CastRay& ray, const Wall& wall, int wall_index) const
{
    const geom::Vector2 segment = wall.end - wall.start;
    const geom::Vector2 offset = wall.start - ray.origin;
    const float denominator = geom::cross(ray.direction, segment);

    if (std::fabs(denominator) < epsilon)
    {
        return {};
    }

    const float ray_distance = geom::cross(offset, segment) / denominator;
    const float wall_position = geom::cross(offset, ray.direction) / denominator;

    if (ray_distance < 0.0F || ray_distance > max_distance_ || wall_position < 0.0F || wall_position > 1.0F)
    {
        return {};
    }

    return 
    {
        true,
        ray.origin + ray.direction * ray_distance,
        ray_distance,
        ray.angle,
        wall_index,
    };
}
