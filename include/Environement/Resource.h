#ifndef RESOURCE_HEADER
#define RESOURCE_HEADER
#include "../utils/math_utils.h"
#include "../utils/utils.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Resource : public Entity {
  public:
  using Entity::Entity; // Inherit constructors from Entity

  Resource(Vector2 position, float speed, float angle, float radius,
           float energy, Environment *env = nullptr)
    : Entity(position, 0, angle, radius, energy, env = nullptr) {
    type = EntityType::RESOURCE;
  }

  virtual void die() override { isAlive = false; }
  virtual EntityType getType() const override { return EntityType::RESOURCE; }
  virtual void interact(std::shared_ptr<Entity> other) override { return; };
};

#endif