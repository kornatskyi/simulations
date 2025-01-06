#include <cmath>
#include <model/Physics/SpatialHashGrid.h>
#include <set>

SpatialHashGrid::SpatialHashGrid(float cellSize) : cellSize(cellSize) {}

void SpatialHashGrid::clear() { grid.clear(); }

bool SpatialHashGrid::checkAABBCollision(std::shared_ptr<Entity> a,
                                         std::shared_ptr<Entity> b) {
  float dx = a->getPosition().x - b->getPosition().x;
  float dy = a->getPosition().y - b->getPosition().y;
  float distanceSquared = dx * dx + dy * dy;

  float radiusSum = a->getRadius() + b->getRadius();
  return distanceSquared < (radiusSum * radiusSum);
}

// Retrieves all potential collisions
std::shared_ptr<std::vector<std::shared_ptr<Entity>>>
SpatialHashGrid::retrieve(std::shared_ptr<Entity> entity) {
  std::set<std::shared_ptr<Entity>> entities;

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
  return std::make_shared<std::vector<std::shared_ptr<Entity>>>(
      entities.begin(), entities.end());
}

std::string SpatialHashGrid::getCellKey(int x, int y) {
  return std::to_string(x) + "," + std::to_string(y);
}

void SpatialHashGrid::insert(std::shared_ptr<Entity> entity) {
  auto cellIndices = getCellIndices(entity);

  for (auto index : cellIndices) {
    if (grid.find(index) == grid.end()) {
      std::shared_ptr<std::vector<std::shared_ptr<Entity>>> newVec =
          std::make_shared<std::vector<std::shared_ptr<Entity>>>();

      grid.emplace(index, newVec);
    }
    grid.at(index)->push_back(entity);
  }
}

std::vector<std::string>
SpatialHashGrid::getCellIndices(std::shared_ptr<Entity> entity) {
  std::set<std::string> indices;

  // Probably what you want:
  int minX =
      std::floor((entity->getPosition().x - entity->getRadius()) / cellSize);
  int minY =
      std::floor((entity->getPosition().y - entity->getRadius()) / cellSize);
  int maxX =
      std::floor((entity->getPosition().x + entity->getRadius()) / cellSize);
  int maxY =
      std::floor((entity->getPosition().y + entity->getRadius()) / cellSize);

  for (int x = minX; x < maxX; x++) {
    for (int y = minY; y < maxY; y++) {
      indices.insert(getCellKey(x, y));
    }
  }

  return std::vector(indices.begin(), indices.end());
}

void printSet(const std::set<std::string> &s) {
  for (const auto &el : s) {
    std::cout << el << " ";
  }
  std::cout << std::endl;
}