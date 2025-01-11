#include "Physics.h"
#include <algorithm>
#include <cmath>
#include <model/Physics/SpatialHashGrid.h>
#include <set>

SpatialHashGrid::SpatialHashGrid(float cellSize) : cellSize(cellSize) {}

std::unordered_map<std::uint64_t, std::vector<EntityPtr>>
SpatialHashGrid::getGrid() {
  return grid;
}

std::tuple<int, int> SpatialHashGrid::unhashCellIndices(std::uint64_t cellKey) {
  // The upper 32 bits represent x, and the lower 32 bits represent y.
  auto x = static_cast<int>(static_cast<std::uint32_t>(cellKey >> 32));
  auto y = static_cast<int>(static_cast<std::uint32_t>(cellKey & 0xFFFFFFFF));
  return std::tuple<int, int>(x, y);
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
std::vector<EntityPtr>
SpatialHashGrid::getPotentialCollisions(EntityPtr entity) {
  std::unordered_set<EntityPtr> entities;

  auto cellIndices = getCellIndices(entity);

  for (auto index : cellIndices) {
    auto it = grid.find(index);
    if (it != grid.end()) {
      const auto &cellEntities = it->second; // a reference to the vector
      entities.insert(cellEntities.begin(), cellEntities.end());
    }
  }
  entities.erase(entity);

  return std::vector<EntityPtr>(entities.begin(), entities.end());
}

// Retrieves all potential collisions
std::vector<EntityPair> SpatialHashGrid::getAllCollisionPairs() {

  std::unordered_set<EntityPair> pairs;

  for (auto &[key, value] : grid) {
    for (size_t i = 0; i < value.size() - 1; i++) {
      for (size_t j = i + 1; j < value.size(); j++) {
        pairs.insert(EntityPair{value[i], value[j]});
      }
    }
  }
  return std::vector<EntityPair>(pairs.begin(), pairs.end());
}

std::uint64_t SpatialHashGrid::hashCellIndices(int x, int y) {
  // shift x by 32 bits and combine
  return (static_cast<std::uint64_t>(static_cast<std::uint32_t>(x)) << 32) |
         static_cast<std::uint32_t>(y);
}

void SpatialHashGrid::addEntity(EntityPtr entity) {
  auto cellIndices = getCellIndices(entity);

  for (auto index : cellIndices) {
    grid[index].push_back(entity);
  }
}

std::vector<std::uint64_t> SpatialHashGrid::getCellIndices(EntityPtr entity) {
  std::set<std::uint64_t> indices;

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
      indices.insert(hashCellIndices(x, y - 1));
    }
  }

  return std::vector<std::uint64_t>(indices.begin(), indices.end());
}
