#include "Physics.h"
#include <Config.h>

// Constructor
Physics::Physics(float cellSize) : cellSize(cellSize), spatialGrid(cellSize) {
  for (unsigned int i = 0; i < Config::getInstance().width / cellSize; ++i) {
    for (unsigned int j = 0; j < Config::getInstance().height / cellSize; ++j) {
      entitiesByCell[Cell(i, j)] = EntitiesSet();
    }
  }
}

// Get all cells
std::vector<Cell> Physics::getCells() {
  std::vector<Cell> cells;
  for (auto [cell, _] : entitiesByCell) {
    cells.push_back(cell);
  }
  return cells;
}

// Get cell size
float Physics::getCellSize() { return cellSize; }

// Get the cell corresponding to a specific position
Cell Physics::getCell(Vector2 p) {
  return Cell(p.x / cellSize, p.y / cellSize);
}

// Check if two entities are colliding
bool Physics::areColliding(const EntityPtr &e1, const EntityPtr &e2) const {
  float dx = e2->getPosition().x - e1->getPosition().x;
  float dy = e2->getPosition().y - e1->getPosition().y;
  return e1->getRadius() + e2->getRadius() >= std::hypot(dx, dy);
}

// Update the spatial partitioning based on entity positions
void Physics::update(const std::vector<EntityPtr> &entities) {
  for (auto &[cell, _] : entitiesByCell) {
    _ = EntitiesSet(); // Clear existing entities in cell
  }

  for (const auto &entity : entities) {
    Cell cell(entity->getPosition().x / cellSize,
              entity->getPosition().y / cellSize);
    entitiesByCell[cell].insert(entity);
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