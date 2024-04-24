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

  explicit Physics(float cellSize = 100) : cellSize(cellSize) {
    for (unsigned int i = 0; i < Config::WIDTH / cellSize; ++i) {
      for (unsigned int j = 0; j < Config::HEIGHT / cellSize; ++j) {
        entitiesByCell[Cell(i, j)] = EntitiesSet();
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

  inline Cell getCell(Vector2 p) {
    return std::tuple<int, int>{p.x / cellSize, p.y / cellSize};
  }
  /// @brief Returns a set of tuples of entities that are colliding.
  /// @param entities
  /// @return
  std::set<EntityPair>
  getCollidingEntities(const std::vector<EntityPtr> &entities) {
    // First, update the spatial partitioning or any necessary pre-processing.
    update(entities);

    std::set<EntityPair> collidingPairs;

    // Utility lambda to check and handle potential collisions with entities in
    // a specific cell
    auto checkAndHandleCollisions = [&](const std::shared_ptr<Entity> &e1,
                                        const Vector2 &offset) {
      auto cell =
        getCell(Vector2(e1->position.x + offset.x, e1->position.y + offset.y));
      auto it = entitiesByCell.find(cell);
      if (it != entitiesByCell.end()) {
        for (auto e2 : it->second) {
          bool isCollisionAlreadyDetected =
            collidingPairs.find(EntityPair{e2, e1}) == collidingPairs.end();
          if (e1 != e2 && isCollisionAlreadyDetected && areColliding(e1, e2)) {
            collidingPairs.insert(EntityPair{e1, e2});
          }
        }
      }
    };

    // Check current cell and adjacent cells for collisions
    for (auto e1 : entities) {
      // Current cell
      checkAndHandleCollisions(e1, Vector2(0, 0));
      // Check left
      if (fmod(e1->position.x, cellSize) < e1->radius) {
        checkAndHandleCollisions(e1, Vector2(-cellSize, 0));
      }
      // Check right
      if (fmod(cellSize - fmod(e1->position.x, cellSize), cellSize) <
          e1->radius) {
        checkAndHandleCollisions(e1, Vector2(cellSize, 0));
      }
      // Check above
      if (fmod(e1->position.y, cellSize) < e1->radius) {
        checkAndHandleCollisions(e1, Vector2(0, -cellSize));
      }
      // Check below
      if (fmod(cellSize - fmod(e1->position.y, cellSize), cellSize) <
          e1->radius) {
        checkAndHandleCollisions(e1, Vector2(0, cellSize));
      }
      // Diagonal checks
      // Top-left
      if (fmod(e1->position.x, cellSize) < e1->radius &&
          fmod(e1->position.y, cellSize) < e1->radius) {
        checkAndHandleCollisions(e1, Vector2(-cellSize, -cellSize));
      }
      // Top-right
      if (fmod(cellSize - fmod(e1->position.x, cellSize), cellSize) <
            e1->radius &&
          fmod(e1->position.y, cellSize) < e1->radius) {
        checkAndHandleCollisions(e1, Vector2(cellSize, -cellSize));
      }
      // Bottom-left
      if (fmod(e1->position.x, cellSize) < e1->radius &&
          fmod(cellSize - fmod(e1->position.y, cellSize), cellSize) <
            e1->radius) {
        checkAndHandleCollisions(e1, Vector2(-cellSize, cellSize));
      }
      // Bottom-right
      if (fmod(cellSize - fmod(e1->position.x, cellSize), cellSize) <
            e1->radius &&
          fmod(cellSize - fmod(e1->position.y, cellSize), cellSize) <
            e1->radius) {
        checkAndHandleCollisions(e1, Vector2(cellSize, cellSize));
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
      Cell cell(entity->position.x / cellSize, entity->position.y / cellSize);
      entitiesByCell[cell].insert(entity);
    }
  }
};

#endif
