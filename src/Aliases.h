#pragma once

#include <cmath>
#include <memory>
#include <model/Entity/Entity.h>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utils/utils.h>
#include <vector>

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