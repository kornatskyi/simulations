#pragma once

#include <cmath>
#include <map>
#include <memory>
#include <model/Entity/Entity.h>
#include <model/Physics/SpatialHashGrid.h>
#include <set>
#include <tuple>
#include <utils/utils.h>
#include <vector>

class Physics {
public:
  using EntityPtr = std::shared_ptr<Entity>;
  using EntityPair = std::tuple<EntityPtr, EntityPtr>;
  using Cell = std::tuple<int, int>;
  using EntitiesSet = std::set<EntityPtr>;
  using EntityMap = std::map<Cell, EntitiesSet>;

  explicit Physics(float cellSize = 50);

  std::vector<Cell> getCells();
  float getCellSize();
  Cell getCell(Vector2 p);

  std::set<EntityPair>
  getCollidingEntities(const std::vector<EntityPtr> &entities);

private:
  EntityMap entitiesByCell;
  float cellSize;
  SpatialHashGrid spatialGrid;

  bool areColliding(const EntityPtr &e1, const EntityPtr &e2) const;
  void update(const std::vector<EntityPtr> &entities);
};
