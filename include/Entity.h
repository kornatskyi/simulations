#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <tuple>

// Forward declaration for Environment
class Environment;

enum class EntityType { ENTITY, CARNIVORE, HERBIVORE, RESOURCE };

class Entity {
  public:
  Vector2 position;
  float speed;
  float angle;
  float radius;
  float energy;
  bool isAlive;
  Environment *env;

  // Default constructor simplified
  Entity()
    : position(0.f, 0.f), speed(0.1f), angle(0.f), radius(20.f), energy(0.f),
      isAlive(true), env(nullptr) {}

  // Parameterized constructor with default parameters removed for clarity
  Entity(Vector2 position, float speed, float angle, float radius, float energy,
         Environment *env = nullptr)
    : position(position), speed(speed), angle(angle), radius(radius),
      energy(energy), isAlive(true), env(env) {}

  virtual ~Entity() = default; // Virtual destructor for base class

  void moveForward(float elapsedTime) {
    auto [newAngle, newPos] =
      adjustMovementForWalls(position, angle, Config::WIDTH, Config::HEIGHT);
    angle = newAngle;
    position.x += std::cos(dToR(angle)) * speed * elapsedTime;
    position.y += std::sin(dToR(angle)) * speed * elapsedTime;
  }

  virtual float die() {
    isAlive = false;
    float releasedEnergy = energy;
    energy = 0.f;
    return releasedEnergy;
  }

  inline std::string getLabel() const {
    return "Entity: " + std::to_string(position.x) + ", " +
           std::to_string(position.y);
  }

  virtual EntityType getType() const { return EntityType::ENTITY; }

  // Comparison operators streamlined with std::tie for readability and
  // maintainability
  bool operator<(const Entity &other) const {
    return std::tie(position.x, position.y, speed, angle, radius, energy) <
           std::tie(other.position.x, other.position.y, other.speed,
                    other.angle, other.radius, other.energy);
  }

  bool operator==(const Entity &other) const {
    return std::tie(position.x, position.y, speed, angle, radius, energy,
                    isAlive) == std::tie(other.position.x, other.position.y,
                                         other.speed, other.angle, other.radius,
                                         other.energy, other.isAlive);
  }

  private:
  // Helper method to adjust entity movement if colliding with walls
  static std::tuple<float, Vector2> adjustMovementForWalls(Vector2 position,
                                                           float angle,
                                                           float maxWidth,
                                                           float maxHeight) {
    if (position.x < 0 || position.x > maxWidth)
      angle = 180.f - angle;
    if (position.y < 0 || position.y > maxHeight)
      angle = 360.f - angle;
    return {angle, position};
  }
};

#endif
