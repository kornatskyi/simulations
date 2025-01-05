#include "Entity.h"
#include <utils/math_utils.h>

// Default constructor
Entity::Entity()
    : position(0.f, 0.f), speed(0.1f), angle(0.f), radius(20.f), energy(0.f),
      isAlive(true), env(nullptr) {
  type = EntityType::ENTITY;
}

// Parameterized constructor
Entity::Entity(Vector2 position, float speed, float angle, float radius,
               float energy, Environment *env)
    : position(position), speed(speed), angle(angle), radius(radius),
      energy(energy), isAlive(true), env(env) {
  type = EntityType::ENTITY;
}

// Move the entity forward based on elapsed time
void Entity::moveForward(float elapsedTime) {
  auto [newAngle, newPos] =
      adjustMovementForWalls(position, angle, Config::WIDTH, Config::HEIGHT);
  position = newPos;
  angle = newAngle;
  position.x += std::cos(MathUtils::dToR(angle)) * speed * elapsedTime;
  position.y += std::sin(MathUtils::dToR(angle)) * speed * elapsedTime;
}

// Get entity label
std::string Entity::getLabel() const {
  return "Entity: " + std::to_string(position.x) + ", " +
         std::to_string(position.y);
}

// Get entity type
EntityType Entity::getType() const { return type; }

// Comparison operators
bool Entity::operator<(const Entity &other) const {
  return std::tie(position.x, position.y, speed, angle, radius, energy) <
         std::tie(other.position.x, other.position.y, other.speed, other.angle,
                  other.radius, other.energy);
}

bool Entity::operator==(const Entity &other) const {
  return std::tie(position.x, position.y, speed, angle, radius, energy,
                  isAlive) == std::tie(other.position.x, other.position.y,
                                       other.speed, other.angle, other.radius,
                                       other.energy, other.isAlive);
}

// Virtual destructor
Entity::~Entity() = default;

// Helper method to adjust entity movement if colliding with walls
std::tuple<float, Vector2> Entity::adjustMovementForWalls(Vector2 position,
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
