#include "Physics.h"
#include <algorithm>
#include <cmath>
#include <model/Physics/SpatialHashGrid.h>
#include <set>

SpatialHashGrid::SpatialHashGrid(float cellSize) : cellSize(cellSize) {}

std::map<std::string, std::shared_ptr<std::vector<EntityPtr>>>
SpatialHashGrid::getGrid() {
  return grid;
}

std::tuple<int, int> SpatialHashGrid::getCellIndex(std::string cellKey) {
  std::istringstream stream(cellKey);
  std::string xStr, yStr;

  // Split the string by comma
  std::getline(stream, xStr, ',');
  std::getline(stream, yStr, ',');

  // Convert to integers and return as tuple
  int x = std::stoi(xStr);
  int y = std::stoi(yStr);

  return std::make_tuple(x, y);
}

void SpatialHashGrid::clear() { grid.clear(); }

bool SpatialHashGrid::areColliding(EntityPtr a, EntityPtr b) {
  float dx = a->getPosition().x - b->getPosition().x;
  float dy = a->getPosition().y - b->getPosition().y;
  float distanceSquared = dx * dx + dy * dy;

  float radiusSum = a->getRadius() + b->getRadius();
  return distanceSquared < (radiusSum * radiusSum);
}

// Retrieves all potential collisions
std::shared_ptr<std::vector<EntityPtr>>
SpatialHashGrid::getPotentialCollisions(EntityPtr entity) {
  std::set<EntityPtr> entities;

  auto cellIndices = getCellIndices(entity);

  for (auto index : cellIndices) {

    if (grid.find(index) != grid.end()) {
      auto cellEntities = grid.at(index);

      for (auto cellEntity : *cellEntities) {
        if (cellEntity != entity) {
          entities.insert(cellEntity);
        }
      }
    }
  }
  return std::make_shared<std::vector<EntityPtr>>(entities.begin(),
                                                  entities.end());
}

std::string SpatialHashGrid::getCellKey(int x, int y) {
  return std::to_string(x) + "," + std::to_string(y);
}

void SpatialHashGrid::addEntity(EntityPtr entity) {
  auto cellIndices = getCellIndices(entity);

  for (auto index : cellIndices) {

    if (grid.find(index) == grid.end()) {
      std::shared_ptr<std::vector<EntityPtr>> newVec =
          std::make_shared<std::vector<EntityPtr>>();

      grid.emplace(index, newVec);
    }
    grid.at(index)->push_back(entity);
  }
}

std::vector<std::string> SpatialHashGrid::getCellIndices(EntityPtr entity) {
  std::set<std::string> indices;

  const float cellSize = EnvConfig::getInstance().spatialCellSize;
  const auto &pos = entity->getPosition();
  const float radius = entity->getRadius();

  // 1. Circle's bounding box
  const float left = pos.x - radius;
  const float right = pos.x + radius;
  const float bottom = pos.y - radius;
  const float top = pos.y + radius;

  // 2. Convert to cell indices
  int minCellX = static_cast<int>(std::floor(left / cellSize));
  int maxCellX = static_cast<int>(std::floor(right / cellSize));
  int minCellY = static_cast<int>(std::floor(bottom / cellSize));
  int maxCellY = static_cast<int>(std::floor(top / cellSize));

  // 3. Insert all touched cells
  for (int x = minCellX; x <= maxCellX; ++x) {
    for (int y = minCellY; y <= maxCellY; ++y) {
      indices.insert(getCellKey(x, y - 1));
    }
  }

  return std::vector<std::string>(indices.begin(), indices.end());
}
