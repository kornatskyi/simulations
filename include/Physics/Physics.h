#ifndef PHYSICS_HEADER
#define PHYSICS_HEADER

#include "../Environement/Entity.h"
#include <cmath>
#include <map>
#include <memory>
#include <set>
#include <tuple>
#include <vector>

class Physics {
  public:
  using EntityPtr = std::shared_ptr<Entity>;
  using EntityPair = std::tuple<EntityPtr, EntityPtr>;
  using Cell = std::tuple<int, int>;
  using EntitiesSet = std::set<EntityPtr>;
  using EntityMap = std::map<Cell, EntitiesSet>;

  explicit Physics(float cellSize = 100.0f) : cellSize(cellSize) {
    for (unsigned int i = 0; i <= Config::WIDTH / cellSize; ++i) {
      for (unsigned int j = 0; j <= Config::HEIGHT / cellSize; ++j) {
        entitiesByCell[Cell(i * cellSize, j * cellSize)] = EntitiesSet();
      }
    }
  }

  std::vector<Cell> getCells() {
    std::vector<Cell> cells;
    for (auto [cell, _] : entitiesByCell) {
      cells.push_back(cell);
    }
    return cells;
  }

  float getCellSize() { return cellSize; }

  std::vector<EntityPair>
  collidingEntities(const std::vector<EntityPtr> &entities) {
    // First, update the spatial partitioning or any necessary pre-processing.
    update(entities);

    std::vector<EntityPair> collidingPairs;

    // Iterate through each cell of entities to check for collisions.
    for (const auto &[cell, entitiesInCell] : entitiesByCell) {
      // Use a double loop to compare each entity with every other entity in the
      // same cell.
      for (auto firstEntityIt = entitiesInCell.begin();
           firstEntityIt != entitiesInCell.end(); ++firstEntityIt) {
        for (auto secondEntityIt = std::next(firstEntityIt);
             secondEntityIt != entitiesInCell.end(); ++secondEntityIt) {
          // If two entities are colliding, add them to the list of colliding
          // pairs.
          if (areColliding(*firstEntityIt, *secondEntityIt)) {
            collidingPairs.emplace_back(*firstEntityIt, *secondEntityIt);
          }
        }
      }
    }

    return collidingPairs;
  }

  private:
  EntityMap entitiesByCell;
  float cellSize;

  inline bool areColliding(const EntityPtr &e1, const EntityPtr &e2) const {
    float dx = e2->position.x - e1->position.x;
    float dy = e2->position.y - e1->position.y;
    return e1->radius + e2->radius >= std::hypot(dx, dy);
  }

  void update(const std::vector<EntityPtr> &entities) {
    for (auto &[cell, _] : entitiesByCell) {
      _ = EntitiesSet(); // Clear existing entities in cell
    }

    for (const auto &entity : entities) {
      Cell cell(int(entity->position.x / cellSize) * cellSize,
                int(entity->position.y / cellSize) * cellSize);
      entitiesByCell[cell].insert(entity);
    }
  }
};

#endif
