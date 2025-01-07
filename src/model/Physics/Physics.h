#pragma once

#include <cmath>
#include <map>
#include <memory>
#include <model/Entity/Entity.h>
#include <model/Physics/SpatialHashGrid.h>
#include <set>
#include <tuple>
#include <unordered_set>
#include <utils/utils.h>
#include <vector>

// Assuming EntityPtr is some pointer or shared_ptr to an entity
using EntityPtr = std::shared_ptr<Entity>;
using EntityPair = std::tuple<EntityPtr, EntityPtr>;
using Cell = std::tuple<int, int>;
using EntitiesSet = std::set<EntityPtr>;
using EntityMap = std::map<Cell, EntitiesSet>;

// Hash combine utility
inline void hash_combine(std::size_t &seed, std::size_t value) {
  seed ^= value + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
}

namespace std {
template <> struct hash<EntityPair> {
  size_t operator()(const EntityPair &pair) const noexcept {
    size_t seed = 0;

    // Extract entity IDs
    auto id1 = std::get<0>(pair)->getId();
    auto id2 = std::get<1>(pair)->getId();

    // Ensure consistent order by sorting the IDs
    if (id1 > id2)
      std::swap(id1, id2);

    // Hash the sorted IDs
    hash_combine(seed, hash<Entity::EntityID>{}(id1));
    hash_combine(seed, hash<Entity::EntityID>{}(id2));

    return seed;
  }
};
} // namespace std

class Physics {
public:
  explicit Physics(float cellSize = EnvConfig::getInstance().spatialCellSize);

  std::vector<Cell> getCells();
  float getCellSize();
  Cell getCell(Vector2 p);

  std::unordered_set<EntityPair>
  getCollidingEntities(const std::vector<EntityPtr> &entities);

private:
  EntityMap entitiesByCell;
  float cellSize;
  SpatialHashGrid spatialGrid;

  bool areColliding(const EntityPtr &e1, const EntityPtr &e2) const;
  void update(const std::vector<EntityPtr> &entities);
};
