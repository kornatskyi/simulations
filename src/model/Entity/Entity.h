#pragma once

#include <EnvConfig.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <random>
#include <tuple>
#include <utils/utils.h>

// Forward declaration for Environment
class Environment;

enum class EntityType { ENTITY, CARNIVORE, HERBIVORE, RESOURCE };

class Entity {
public:
  using EntityID = std::size_t;

  Entity();
  Entity(Environment *env = nullptr);

  virtual ~Entity();

  virtual void moveForward(float elapsedTime);
  virtual void die();
  std::string getLabel() const;
  virtual EntityType getType() const;

  bool alive() const;
  Vector2 getPosition() const;
  Entity &setPosition(const Vector2 &newPos);

  float getEnergy() const;
  Entity &setEnergy(float newEnergy);

  float getRadius() const;
  Entity &setRadius(float newRadius);

  float getAngle() const;
  Entity &setAngle(float newAngle);

  float getSpeed() const;
  Entity &setSpeed(float newSpeed);

  bool operator<(const Entity &other) const;
  bool operator==(const Entity &other) const;

  virtual void interact(std::shared_ptr<Entity> other) = 0;
  virtual std::shared_ptr<Entity> reproduce() = 0;

  EntityID getId() { return id_; }

  static EntityID generateId() {
    static std::random_device rd;
    static std::mt19937_64 gen(rd()); // 64-bit Mersenne Twister
    return gen();
  }

protected:
  Vector2 position = Vector2(0, 0);
  float speed = EnvConfig::getInstance().entitySpeed;
  float angle = 360;
  float radius = EnvConfig::getInstance().entityRadius;
  float energy = EnvConfig::getInstance().entityEnergy;
  bool isAlive = true;
  Environment *env;
  EntityType type;
  EntityID id_;

private:
  static std::tuple<float, Vector2> adjustMovementForWalls(Vector2 position,
                                                           float angle,
                                                           float maxWidth,
                                                           float maxHeight);
};
