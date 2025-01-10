#include "Physics.h"
#include <Config.h>

// Constructor
Physics::Physics(float cellSize) : cellSize(cellSize), spatialGrid(cellSize) {}

// Get cell size
float Physics::getCellSize() { return cellSize; }

// Check if two entities are colliding
bool Physics::areColliding(const EntityPtr &e1, const EntityPtr &e2) const {
  float dx = e2->getPosition().x - e1->getPosition().x;
  float dy = e2->getPosition().y - e1->getPosition().y;
  return e1->getRadius() + e2->getRadius() >= std::hypot(dx, dy);
}

// Update the spatial partitioning based on entity positions
void Physics::update(const std::vector<EntityPtr> &entities) {
  spatialGrid.clear();
  // Update entity positions and insert them into the grid
  for (auto &entity : entities) {
    spatialGrid.addEntity(entity);
  }
}

std::unordered_set<EntityPair>
Physics::getCollidingEntities(const std::vector<EntityPtr> &entities) {

  spatialGrid.clear();
  // Update entity positions and insert them into the grid
  for (auto &entity : entities) {
    spatialGrid.addEntity(entity);
  }

  std::unordered_set<EntityPair> collidingPairs;

  for (auto &entity : entities) {

    auto potentiallyCollidingWith = spatialGrid.getPotentialCollisions(entity);

    for (auto ent : *potentiallyCollidingWith) {
      if (spatialGrid.areColliding(entity, ent)) {
        collidingPairs.insert(EntityPair{entity, ent});
      }
    }
  }

  return collidingPairs;
}

std::shared_ptr<std::vector<EntityPtr>>
Physics::getPotentiallyColliding(const EntityPtr &entity) {

  return spatialGrid.getPotentialCollisions(entity);
}
