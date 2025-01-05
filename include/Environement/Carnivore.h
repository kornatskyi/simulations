#ifndef CARNIVORE_HEADER
#define CARNIVORE_HEADER
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../utils/math_utils.h"
#include "../utils/utils.h"
#include "Entity.h"

class Carnivore : public Entity {
 public:
  using Entity::Entity;  // Inherit constructors from Entity

  Carnivore(Vector2 position, float speed, float angle, float radius,
            float energy, Environment *env = nullptr)
      : Entity(position, speed, angle, radius, energy, env = nullptr) {
    type = EntityType::CARNIVORE;
    lifetime = 10;
  }

  virtual void die() override { isAlive = false; }

  virtual void interact(std::shared_ptr<Entity> other) override {
    if (other->getType() == EntityType::HERBIVORE) {
      other->die();
      energy += other->energy;
    }
  }

  void moveForward(float elapsedTime) override {
    Entity::moveForward(elapsedTime);
    lifetime -= elapsedTime;
    if (lifetime <= 0) {
      die();
    }
  }

  virtual EntityType getType() const override { return EntityType::CARNIVORE; }

  virtual std::shared_ptr<Entity> reproduce() override {
    const float energyToSplit = 10;
    if (energy > energyToSplit) {
      energy -= energyToSplit;
      return std::make_shared<Carnivore>(position, speed, angle - 180, radius,
                                         energyToSplit, env);
    }
    return nullptr;
  }
};

#endif