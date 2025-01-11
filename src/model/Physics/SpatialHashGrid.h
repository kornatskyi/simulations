#pragma once

#include <Aliases.h>
#include <memory>
#include <model/Entity/Entity.h>
#include <unordered_map>
#include <utils/utils.h>
#include <vector>

class SpatialHashGrid {
public:
  SpatialHashGrid(float cellSize);

  void clear();

  bool areColliding(EntityPtr a, EntityPtr b);

  // Retrieves all potential collisions
  std::vector<EntityPtr> getPotentialCollisions(EntityPtr entity);

  std::vector<EntityPair> getAllCollisionPairs();


  void addEntity(EntityPtr entity);

  std::unordered_map<std::uint64_t, std::vector<EntityPtr>> getGrid();
  std::uint64_t hashCellIndices(int x, int y);
  std::tuple<int, int> unhashCellIndices(std::uint64_t cellKey);

private:
  float cellSize;
  std::unordered_map<std::uint64_t, std::vector<EntityPtr>> grid;

  std::vector<std::uint64_t> getCellIndices(EntityPtr entity);
};
