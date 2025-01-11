#pragma once

#include <Aliases.h>
#include <cmath>
#include <functional>
#include <memory>
#include <model/Entity/Entity.h>
#include <model/Physics/SpatialHashGrid.h>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utils/utils.h>
#include <vector>

/**
 * @file Physics.h
 * @brief Defines the Physics class responsible for spatial partitioning and
 * collision detection.
 */

// Physics Class Declaration

/**
 * @class Physics
 * @brief Manages spatial partitioning and collision detection among entities.
 *
 * The Physics class utilizes a spatial hash grid to efficiently detect and
 * manage collisions between entities within a simulation or game environment.
 */
class Physics {
public:
  /**
   * @brief Constructs a Physics instance with a specified cell size.
   */
  explicit Physics(float cellSize = Config::getInstance().spatialCellSize);

  /**
   * @brief Gets the size of each cell in the spatial grid.
   *
   * @return float The cell size.
   */
  float getCellSize();

  /**
   * @brief Identifies and returns all pairs of entities that are colliding.
   */
 std::unordered_set<EntityPair>  getAllCollidingPairs();

  /**
   * @brief Updates the spatial grid with the current positions of entities.
   * grid.
   */
  void update(const std::vector<EntityPtr> &entities);

  void runOnInteraction(std::function<void()> myFunc);

  /**
   * @brief The size of each cell in the spatial grid.
   */
  float cellSize;

  /**
   * @brief The spatial hash grid used for partitioning entities.
   *
   * SpatialHashGrid manages the assignment of entities to cells and provides
   * methods to query potential collisions based on spatial locality.
   */
  SpatialHashGrid spatialGrid;

private:
  /**
   * @brief Determines if two entities are colliding.
   *
   * Performs a collision check between two entities, typically by comparing
   * their bounding volumes or performing more detailed physics-based checks.
   *
   * @param e1 The first entity.
   * @param e2 The second entity.
   * @return true If the entities are colliding.
   * @return false Otherwise.
   */
  bool areColliding(const EntityPtr &e1, const EntityPtr &e2) const;
};
