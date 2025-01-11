#pragma once

#include <Aliases.h>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <memory>
#include <model/Entity/Entity.h>
#include <model/Physics/SpatialHashGrid.h>
#include <set>
#include <tuple>
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
   *
   * Initializes the spatial grid based on the provided cell size. If no cell
   * size is specified, it defaults to the value retrieved from the environment
   * configuration.
   *
   * @param cellSize The size of each cell in the spatial grid. Defaults to
   *                 Config::getInstance().spatialCellSize.
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
   *
   * This function performs collision detection by:
   * 1. Clearing the current spatial grid.
   * 2. Updating entity positions and inserting them into the grid.
   * 3. Iterating through each entity to find potential collisions.
   * 4. Checking actual collisions and storing colliding pairs.
   *
   * The resulting unordered_set ensures that each colliding pair is unique.
   *
   * @param entities A vector of EntityPtr objects representing all entities to
   * check.
   * @return std::unordered_set<EntityPair> A set of unique colliding entity
   * pairs.
   */
  std::unordered_set<EntityPair>
  getCollidingEntities(const std::vector<EntityPtr> &entities);

std::vector<EntityPtr>
  getPotentiallyColliding(const EntityPtr &entity);

  /**
   * @brief Updates the spatial grid with the current positions of entities.
   *
   * Processes the provided entities, updating their positions in the spatial
   * grid to reflect any movements or changes since the last update.
   *
   * @param entities A vector of EntityPtr objects to update in the spatial
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
