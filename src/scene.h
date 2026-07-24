#pragma once

#include "wall.h"

#include <vector>

class Scene
{
public:
    void addWall(Wall wall);

    const std::vector<Wall>& getWalls() const;

private:
    std::vector<Wall> walls_;
};
