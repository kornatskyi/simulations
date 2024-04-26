#ifndef CARNIVORE_HEADER
#define CARNIVORE_HEADER
#include "../utils/math_utils.h"
#include "../utils/utils.h"
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Carnivore : public Entity {
  public:
  using Entity::Entity; // Inherit constructors from Entity

  virtual void die() override { isAlive = false; }

  virtual void interact(std::shared_ptr<Entity> other) override {
    if (other->getType() == EntityType::HERBIVORE) {
      other->die();
      energy += other->energy;
    }
  }

  void moveForward(float elapsedTime) override {
    Entity::moveForward(elapsedTime);
    lifetime -= (10 * elapsedTime);
    if (lifetime <= 0) {
      die();
    }
  }

  virtual EntityType getType() const override { return EntityType::CARNIVORE; }
};

#endif