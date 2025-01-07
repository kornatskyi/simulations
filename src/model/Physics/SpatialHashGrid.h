#pragma once

#include <map>
#include <memory>
#include <model/Entity/Entity.h>
#include <utils/utils.h>
#include <vector>

class SpatialHashGrid {
public:
  SpatialHashGrid(float cellSize);

  void clear();

  bool areColliding(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);

  // Retrieves all potential collisions
  std::shared_ptr<std::vector<std::shared_ptr<Entity>>>
  getPotentialCollisions(std::shared_ptr<Entity> entity);
  void addEntity(std::shared_ptr<Entity> entity);

private:
  float cellSize;
  std::map<std::string, std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>
      grid;

  std::string getCellKey(int x, int y);
  std::vector<std::string> getCellIndices(std::shared_ptr<Entity> entity);
};
