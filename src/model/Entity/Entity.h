#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <tuple>
#include <utils/utils.h>

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

  Entity();
  Entity(Vector2 position, float speed, float angle, float radius, float energy,
         Environment *env = nullptr);

  virtual void moveForward(float elapsedTime);
  virtual void die() = 0;
  std::string getLabel() const;
  virtual EntityType getType() const;
  virtual void interact(std::shared_ptr<Entity> other) = 0;
  virtual std::shared_ptr<Entity> reproduce() = 0;

  bool operator<(const Entity &other) const;
  bool operator==(const Entity &other) const;

  virtual ~Entity();

private:
  static std::tuple<float, Vector2> adjustMovementForWalls(Vector2 position,
                                                           float angle,
                                                           float maxWidth,
                                                           float maxHeight);
};
