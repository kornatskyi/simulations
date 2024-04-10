#ifndef RESOURCE_HEADER
#define RESOURCE_HEADER
#include "Entity.h"
#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Resource : public Entity {
  public:
  using Entity::Entity; // Inherit constructors from Entity

  virtual float die() override {
    isAlive = false;
    float deltaEnergy = energy;
    energy = 0;
    return deltaEnergy;
  }
  virtual EntityType getType() const override { return EntityType::RESOURCE; }
};

#endif