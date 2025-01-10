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
  void addEntity(EntityPtr entity);

  std::unordered_map<std::string, std::vector<EntityPtr>> getGrid();
  std::tuple<int, int> getCellIndex(std::string cellKey);

private:
  float cellSize;
  std::unordered_map<std::string, std::vector<EntityPtr>> grid;

  std::string getCellKey(int x, int y);
  std::vector<std::string> getCellIndices(EntityPtr entity);
};
