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
std::vector<Physics::Cell> Physics::getCells() {
  std::vector<Cell> cells;
  for (auto [cell, _] : entitiesByCell) {
    cells.push_back(cell);
  }
  return cells;
}

// Get cell size
float Physics::getCellSize() { return cellSize; }

// Get the cell corresponding to a specific position
Physics::Cell Physics::getCell(Vector2 p) {
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

std::set<Physics::EntityPair>
Physics::getCollidingEntities(const std::vector<EntityPtr> &entities) {

  spatialGrid.clear();
  // Update entity positions and insert them into the grid
  for (auto &entity : entities) {
    spatialGrid.insert(entity);
  }

  std::set<EntityPair> collidingPairs;

  for (auto &entity : entities) {
    auto potentiallyCollidingWith = spatialGrid.retrieve(entity);
    for (auto ent : *potentiallyCollidingWith) {
      if (spatialGrid.checkAABBCollision(entity, ent)) {
        collidingPairs.insert(EntityPair{entity, ent});
      }
    }
  }

  return collidingPairs;
}

// Get colliding entities based on spatial partitioning
// std::set<Physics::EntityPair>
// Physics::getCollidingEntities(const std::vector<EntityPtr> &entities) {
//   update(entities);

//   std::set<EntityPair> collidingPairs;

//   auto checkAndHandleCollisions = [&](const std::shared_ptr<Entity> &e1,
//                                       const Vector2 &offset) {
//     auto cell = getCell(Vector2(e1->getPosition().x + offset.x,
//                                 e1->getPosition().y + offset.y));
//     auto it = entitiesByCell.find(cell);
//     if (it != entitiesByCell.end()) {
//       for (auto e2 : it->second) {
//         bool isCollisionAlreadyDetected =
//             collidingPairs.find(EntityPair{e2, e1}) != collidingPairs.end();
//         if (e1 != e2 && !isCollisionAlreadyDetected && areColliding(e1, e2))
//         {
//           collidingPairs.insert(EntityPair{e1, e2});
//         }
//       }
//     }
//   };

//   for (auto e1 : entities) {
//     checkAndHandleCollisions(e1, Vector2(0, 0));
//     if (fmod(e1->getPosition().x, cellSize) < e1->getRadius()) {
//       checkAndHandleCollisions(e1, Vector2(-cellSize, 0));
//     }
//     if (fmod(cellSize - fmod(e1->getPosition().x, cellSize), cellSize) <
//         e1->getRadius()) {
//       checkAndHandleCollisions(e1, Vector2(cellSize, 0));
//     }
//     if (fmod(e1->getPosition().y, cellSize) < e1->getRadius()) {
//       checkAndHandleCollisions(e1, Vector2(0, -cellSize));
//     }
//     if (fmod(cellSize - fmod(e1->getPosition().y, cellSize), cellSize) <
//         e1->getRadius()) {
//       checkAndHandleCollisions(e1, Vector2(0, cellSize));
//     }
//     if (fmod(e1->getPosition().x, cellSize) < e1->getRadius() &&
//         fmod(e1->getPosition().y, cellSize) < e1->getRadius()) {
//       checkAndHandleCollisions(e1, Vector2(-cellSize, -cellSize));
//     }
//     if (fmod(cellSize - fmod(e1->getPosition().x, cellSize), cellSize) <
//             e1->getRadius() &&
//         fmod(e1->getPosition().y, cellSize) < e1->getRadius()) {
//       checkAndHandleCollisions(e1, Vector2(cellSize, -cellSize));
//     }
//     if (fmod(e1->getPosition().x, cellSize) < e1->getRadius() &&
//         fmod(cellSize - fmod(e1->getPosition().y, cellSize), cellSize) <
//             e1->getRadius()) {
//       checkAndHandleCollisions(e1, Vector2(-cellSize, cellSize));
//     }
//     if (fmod(cellSize - fmod(e1->getPosition().x, cellSize), cellSize) <
//             e1->getRadius() &&
//         fmod(cellSize - fmod(e1->getPosition().y, cellSize), cellSize) <
//             e1->getRadius()) {
//       checkAndHandleCollisions(e1, Vector2(cellSize, cellSize));
//     }
//   }

//   return collidingPairs;
// }
