#pragma once

#include "geometry.h"

#include <raylib.h>

struct Wall
{
    geom::Vector2 start{};
    geom::Vector2 end{};
    Color color{ WHITE };
};
