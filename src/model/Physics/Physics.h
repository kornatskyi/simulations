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

/**
 * @file Physics.h
 * @brief Defines the Physics class responsible for spatial partitioning and
 * collision detection.
 */

// Type Definitions

/**
 * @typedef EntityPtr
 * @brief Alias for a shared pointer to an Entity object.
 */
using EntityPtr = std::shared_ptr<Entity>;

/**
 * @typedef EntityPair
 * @brief Alias for a tuple containing two EntityPtr objects, representing a
 * pair of entities.
 */
using EntityPair = std::tuple<EntityPtr, EntityPtr>;

/**
 * @typedef Cell
 * @brief Alias for a tuple containing two integers, representing a grid cell's
 * coordinates.
 */
using Cell = std::tuple<int, int>;

/**
 * @typedef EntitiesSet
 * @brief Alias for a set of EntityPtr objects, representing entities within a
 * cell.
 */
using EntitiesSet = std::set<EntityPtr>;

/**
 * @typedef EntityMap
 * @brief Alias for a map that associates a Cell with its corresponding
 * EntitiesSet.
 */
using EntityMap = std::map<Cell, EntitiesSet>;

// Utility Functions

/**
 * @brief Combines two hash values into a single hash value.
 *
 * Inspired by Boost's hash_combine, this function provides a way to combine
 * the hashes of multiple objects into a single hash value, which is useful for
 * hashing composite types.
 *
 * @param seed The initial hash value to combine with.
 * @param value The hash value to combine into the seed.
 */
inline void hash_combine(std::size_t &seed, std::size_t value) {
  // This uses a magic constant and bit shifting to combine hashes
  seed ^= value + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
}

// Equality Operator for EntityPair

/**
 * @brief Equality operator for EntityPair.
 *
 * Determines if two EntityPair instances are equal by comparing their entity
 * IDs. The entity IDs are sorted to ensure that the order of entities does not
 * affect equality.
 *
 * @param lhs The first EntityPair to compare.
 * @param rhs The second EntityPair to compare.
 * @return true if both pairs contain the same entities, regardless of order.
 * @return false otherwise.
 */
inline bool operator==(const EntityPair &lhs, const EntityPair &rhs) {
  // Extract entity IDs from the first pair
  auto lhs1 = std::get<0>(lhs)->getId();
  auto lhs2 = std::get<1>(lhs)->getId();

  // Extract entity IDs from the second pair
  auto rhs1 = std::get<0>(rhs)->getId();
  auto rhs2 = std::get<1>(rhs)->getId();

  // Sort IDs of the first pair to ensure consistent ordering
  if (lhs1 > lhs2)
    std::swap(lhs1, lhs2);

  // Sort IDs of the second pair to ensure consistent ordering
  if (rhs1 > rhs2)
    std::swap(rhs1, rhs2);

  // Compare the sorted IDs for equality
  return lhs1 == rhs1 && lhs2 == rhs2;
}

// Specialization of std::hash for EntityPair

namespace std {

/**
 * @struct hash<EntityPair>
 * @brief Specialization of std::hash for the EntityPair type.
 *
 * This allows EntityPair to be used as a key in unordered containers by
 * providing a way to compute its hash value based on the IDs of the contained
 * entities.
 */
template <> struct hash<EntityPair> {
  /**
   * @brief Computes the hash value for an EntityPair.
   *
   * The hash is computed by:
   * 1. Extracting the IDs of both entities in the pair.
   * 2. Sorting the IDs to ensure consistent ordering.
   * 3. Combining the hashes of the sorted IDs.
   *
   * @param pair The EntityPair to hash.
   * @return size_t The resulting hash value.
   */
  size_t operator()(const EntityPair &pair) const noexcept {
    size_t seed = 0;

    // Extract entity IDs from the pair
    auto id1 = std::get<0>(pair)->getId();
    auto id2 = std::get<1>(pair)->getId();

    // Ensure consistent order by sorting the IDs
    if (id1 > id2)
      std::swap(id1, id2);

    // Combine the hash of the first sorted ID
    hash_combine(seed, hash<Entity::EntityID>{}(id1));

    // Combine the hash of the second sorted ID
    hash_combine(seed, hash<Entity::EntityID>{}(id2));

    return seed;
  }
};

} // namespace std

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
   *                 EnvConfig::getInstance().spatialCellSize.
   */
  explicit Physics(float cellSize = EnvConfig::getInstance().spatialCellSize);

  /**
   * @brief Retrieves all occupied cells in the spatial grid.
   *
   * @return std::vector<Cell> A vector containing all cells that currently have
   * entities.
   */
  std::vector<Cell> getCells();

  /**
   * @brief Gets the size of each cell in the spatial grid.
   *
   * @return float The cell size.
   */
  float getCellSize();

  /**
   * @brief Determines the cell coordinates for a given position.
   *
   * Converts a 2D position vector into its corresponding cell coordinates based
   * on the grid's cell size.
   *
   * @param p The position vector.
   * @return Cell The cell coordinates as a tuple of integers.
   */
  Cell getCell(Vector2 p);

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

private:
  /**
   * @brief Maps cells to the set of entities contained within them.
   *
   * This spatial partitioning allows for efficient querying of potential
   * collisions by limiting collision checks to entities within the same or
   * neighboring cells.
   */
  EntityMap entitiesByCell;

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
};
