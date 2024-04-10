#ifndef RESOURCE_HEADER
#define RESOURCE_HEADER
#include "Entity.h"
#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Resource : public Entity {
  public:
  EntityType type = EntityType::RESOURCE;

  virtual float die() override {
    isAlive = false;
    float deltaEnergy = energy;
    energy = 0;
    return deltaEnergy;
  }
};

#endif