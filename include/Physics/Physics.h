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

  std::vector<EntityPair>
  collidingEntities(const std::vector<EntityPtr> &entities) {
    // First, update the spatial partitioning or any necessary pre-processing.
    update(entities);

    std::vector<EntityPair> collidingPairs;

    for (auto e1 : entities) {
      auto cell = getCell(e1->position);
      for (auto e2 : entitiesByCell[cell]) {
        if (e1 != e2 && areColliding(e1, e2)) {
          collidingPairs.emplace_back(e1, e2);
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
      Cell cell(entity->position.x / cellSize, entity->position.y / cellSize);
      entitiesByCell[cell].insert(entity);
    }
  }
};

#endif
