#ifndef PHYSICS_HEADER
#define PHYSICS_HEADER

#include "Entity.h"
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

  std::vector<EntityPair>
  collidingEntities(const std::vector<EntityPtr> &entities) {
    update(entities);

    std::vector<EntityPair> collidingEntities;
    for (const auto &cellEntities : entitiesByCell) {
      for (auto it1 = cellEntities.second.begin();
           it1 != cellEntities.second.end(); ++it1) {
        auto it2 = std::next(it1);
        while (it2 != cellEntities.second.end()) {
          if (areColliding(*it1, *it2)) {
            collidingEntities.emplace_back(*it1, *it2);
          }
          ++it2;
        }
      }
    }
    return collidingEntities;
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
