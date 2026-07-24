#pragma once

#include "camera.h"
#include "geometry.h"
#include "scene.h"

#include <vector>

class Renderer
{
public:
    void drawTopDown(const Scene& scene, const ViewCamera& camera, const std::vector<geom::RayHit>& hits) const;
    void drawFirstPerson(const Scene& scene, const ViewCamera& camera, const std::vector<geom::RayHit>& hits) const;
};
