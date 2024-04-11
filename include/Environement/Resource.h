#ifndef RESOURCE_HEADER
#define RESOURCE_HEADER
#include "Entity.h"
#include "../utils/math_utils.h"
#include "../utils/utils.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Resource : public Entity {
  public:
  using Entity::Entity; // Inherit constructors from Entity

  Resource(Vector2 position, float speed, float angle, float radius,
           float energy, Environment *env = nullptr)
    : Entity(position, 0, angle, radius, energy, env = nullptr) {}

  virtual float die() override {
    isAlive = false;
    float deltaEnergy = energy;
    energy = 0;
    return deltaEnergy;
  }
  virtual EntityType getType() const override { return EntityType::RESOURCE; }
};

#endif