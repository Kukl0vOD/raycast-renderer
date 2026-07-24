#include "scene.h"

void Scene::addWall(Wall wall)
{
    walls_.push_back(wall);
}

const std::vector<Wall>& Scene::getWalls() const
{
    return walls_;
}
