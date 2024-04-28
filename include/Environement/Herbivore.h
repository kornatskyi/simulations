#ifndef HERBIVORE_HEADER
#define HERBIVORE_HEADER
#include "../utils/math_utils.h"
#include "../utils/utils.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Herbivore : public Entity {

  public:
  using Entity::Entity; // Inherit constructors from Entity

  Herbivore(Vector2 position, float speed, float angle, float radius,
            float energy, Environment *env = nullptr)
    : Entity(position, speed, angle, radius, energy, env = nullptr) {
    type = EntityType::HERBIVORE;
  }

  virtual void die() override { isAlive = false; }
  virtual EntityType getType() const override { return EntityType::HERBIVORE; }
  virtual void interact(std::shared_ptr<Entity> other) override {
    if (other->getType() == EntityType::RESOURCE) {
      other->die();
      energy += other->energy;
    }
  }
};

#endif