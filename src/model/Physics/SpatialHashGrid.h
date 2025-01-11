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

  //Reset spatial grid
  void clear();

  // Retrieves all potential collisions
  std::vector<EntityPtr> getPotentialCollisions(EntityPtr entity);

  std::unordered_set<EntityPair> getAllCollidingPairs();

  void addEntity(EntityPtr entity);

  std::unordered_map<std::uint64_t, std::vector<EntityPtr>> getGrid();

  /// @brief converts cell's coordinates to hash value
  std::uint64_t hashCellIndices(int x, int y);

  std::tuple<int, int> unhashCellIndices(std::uint64_t cellKey);

private:
  float cellSize;
  std::unordered_map<std::uint64_t, std::vector<EntityPtr>> grid;

  // @brief returns all cells that this entity is occupying
  std::vector<std::uint64_t> getCellHashesByEntity(EntityPtr entity);
};
