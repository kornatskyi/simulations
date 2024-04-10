#ifndef ENTITY_HEADER
#define ENTITY_HEADER
#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>
// Forward definition for Environemnt
class Environment;

enum EntityType { ENTITY, CARNIVORE, HERBIVORE, RESOURCE };

class Entity {
  public:
  Vector2 position;
  float speed;
  float angle;
  float radius;
  float energy;
  float isAlive = true;
  EntityType type = EntityType::ENTITY;
  Environment *env;

  Entity() {
    position = Vector2(0.f, 0.f);
    speed = 0.f;
    angle = 0.f;
    radius = 20.f;
    energy = 0.0f;
  }
  Entity(Vector2 position = Vector2(0, 0), float speed = 0.1, float angle = 0,
         float radius = 20.f, float energy = 0, Environment *env = NULL)
    : position(position), speed(speed), angle(angle), radius(radius),
      energy(energy), env(env) {}

  void moveForward(float elapsedTime) {
    if (isCollidingWithWall(position)) {
      if (position.x < 0) {
        angle = 180 - angle;
      } else if (position.x > Config::WIDTH) {
        angle = 180 - angle;
      } else if (position.y < 0) {
        angle = 360 - angle;
      } else if (position.y > Config::HEIGHT) {
        angle = 360 - angle;
      }
    }
    position.x = position.x + std::cos(dToR(angle)) * speed * elapsedTime;
    position.y = position.y + std::sin(dToR(angle)) * speed * elapsedTime;
  }

  /// @brief returns energy when dies
  /// @return - energy
  virtual float die() {
    isAlive = false;
    float deltaEnergy = energy;
    energy = 0;
    return deltaEnergy;
  }

  inline std::string getLabel() const {
    return "Entity: " + std::to_string(this->position.x) + ", " +
           std::to_string(this->position.y);
  }

  // Comparison operators
  // Define operator< for comparing Entity objects
  bool operator<(const Entity &other) const {
    // Example comparison logic. Adjust according to your needs.
    return std::tie(position.x, position.y) <
           std::tie(other.position.x, other.position.y);
  }

  bool operator==(const Entity &other) const {
    return position.x == other.position.x && position.y == other.position.y &&
           speed == other.speed && angle == other.angle &&
           radius == other.radius;
  }

  private:
};

#endif
