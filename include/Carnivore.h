#ifndef CARNIVORE_HEADER
#define CARNIVORE_HEADER
#include "Entity.h"
#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Carnivore : public Entity {
  public:
  EntityType type = EntityType::CARNIVORE;

  virtual float die() override {
    isAlive = false;
    float deltaEnergy = energy;
    energy = 0;
    return deltaEnergy;
  }
};

#endif