#ifndef ENTITY_HEADER
#define ENTITY_HEADER

#include "../utils/math_utils.h"
#include "../utils/utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
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
  float lifetime = 10.f;
  EntityType type;

  // Default constructor simplified
  Entity()
    : position(0.f, 0.f), speed(0.1f), angle(0.f), radius(20.f), energy(0.f),
      isAlive(true), env(nullptr) {
    type = EntityType::ENTITY;
  }

  // Parameterized constructor with default parameters removed for clarity
  Entity(Vector2 position, float speed, float angle, float radius, float energy,
         Environment *env = nullptr)
    : position(position), speed(speed), angle(angle), radius(radius),
      energy(energy), isAlive(true), env(env) {
    type = EntityType::ENTITY;
  }

  virtual void moveForward(float elapsedTime) {
    auto [newAngle, newPos] =
      adjustMovementForWalls(position, angle, Config::WIDTH, Config::HEIGHT);
    position = newPos;
    angle = newAngle;
    position.x += std::cos(dToR(angle)) * speed * elapsedTime;
    position.y += std::sin(dToR(angle)) * speed * elapsedTime;
  }

  virtual void die() = 0;

  inline std::string getLabel() const {
    return "Entity: " + std::to_string(position.x) + ", " +
           std::to_string(position.y);
  }

  virtual EntityType getType() const { return type; }

  virtual void interact(std::shared_ptr<Entity> other) = 0;

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

  virtual ~Entity() = default; // Virtual destructor for base class

  private:
  // Helper method to adjust entity movement if colliding with walls
  static std::tuple<float, Vector2> adjustMovementForWalls(Vector2 position,
                                                           float angle,
                                                           float maxWidth,
                                                           float maxHeight) {
    if (position.x < 2) {
      angle = 180.f - angle;
      position.x = 3;
    } else if (position.x > maxWidth - 2) {
      angle = 180.f - angle;
      position.x = maxWidth - 3;
    } else if (position.y < 2) {
      angle = 360.f - angle;
      position.y = 3;
    } else if (position.y > maxHeight - 2) {
      angle = 360.f - angle;
      position.y = maxHeight - 3;
    }
    return {angle, position};
  }
};

// class EntityBuilder {
//   public:
//   EntityBuilder &setPosition(const Vector2 &pos) {
//     entity.position = pos;
//     return *this;
//   }
//   EntityBuilder &setSpeed(float speed) {
//     entity.speed = speed;
//     return *this;
//   }
//   EntityBuilder &setAngle(float angle) {
//     entity.angle = angle;
//     return *this;
//   }
//   EntityBuilder &setRadius(float radius) {
//     entity.radius = radius;
//     return *this;
//   }
//   EntityBuilder &setEnergy(float energy) {
//     entity.energy = energy;
//     return *this;
//   }

//   std::shared_ptr<Entity> build() { return std::make_shared<Entity>(entity);
//   }

//   private:
//   Entity entity;
// };

// class EntityFactory {};

#endif
