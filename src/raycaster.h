#pragma once

#include "camera.h"
#include "geometry.h"
#include "scene.h"

#include <vector>

class Raycaster
{
public:
    Raycaster(int ray_count, float max_distance);

    std::vector<geom::RayHit> cast(const ViewCamera& camera, const Scene& scene) const;
    int rayCount() const;

private:
    geom::RayHit castRay(const geom::CastRay& ray, const Scene& scene) const;
    geom::RayHit intersectWall(const geom::CastRay& ray, const Wall& wall, int wall_index) const;

    int ray_count_{};
    float max_distance_{};
};
