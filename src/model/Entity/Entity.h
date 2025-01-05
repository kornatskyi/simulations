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
  Entity();
  Entity(Vector2 position, float speed, float angle, float radius, float energy,
         Environment *env = nullptr);

  virtual ~Entity();

  virtual void moveForward(float elapsedTime);
  virtual void die();
  std::string getLabel() const;
  virtual EntityType getType() const;

  bool alive() const;
  Vector2 getPosition() const;
  void setPosition(const Vector2 &newPos);

  float getEnergy() const;
  void setEnergy(float newEnergy);

  float getRadius() const;
  void setRadius(float newRadius);

  float getAngle() const;
  void setAngle(float newAngle);

  bool operator<(const Entity &other) const;
  bool operator==(const Entity &other) const;

  virtual void interact(std::shared_ptr<Entity> other) = 0;
  virtual std::shared_ptr<Entity> reproduce() = 0;

protected:
  Vector2 position;
  float speed;
  float angle;
  float radius;
  float energy;
  bool isAlive;
  Environment *env;
  EntityType type;

private:
  static std::tuple<float, Vector2> adjustMovementForWalls(Vector2 position,
                                                           float angle,
                                                           float maxWidth,
                                                           float maxHeight);
};
