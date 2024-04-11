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

  virtual float die() override {
    isAlive = false;
    float deltaEnergy = energy;
    energy = 0;
    return deltaEnergy;
  }
  virtual EntityType getType() const override { return EntityType::HERBIVORE; }
  virtual void interact(std::shared_ptr<Entity> other) override {

    if (other->getType() == EntityType::RESOURCE) {
      other->die();
    }
  }
};

#endif