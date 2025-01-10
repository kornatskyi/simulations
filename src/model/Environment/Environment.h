#pragma once

#include "model/Physics/Physics.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

// Environment.h
class Environment {
public:
  Environment(); // default
  Environment(unsigned int n);

  void update(float elapsedTime);

  // Physics
  std::shared_ptr<Physics> physics;

  // Entities
  std::vector<std::shared_ptr<Entity>> entities;

private:
  // Possibly store one mt19937 engine, seeded once
  std::mt19937 randomEngine;

  // Private helper methods
  void initializeDefaultEntities();
  void generateRandomEntities(unsigned int n);
  void moveEntities(float elapsedTime);
  void handleCollisions();
  void handleReproduction(std::vector<std::shared_ptr<Entity>> &newEntities);
  void
  handleDeathsAndConversions(std::vector<std::shared_ptr<Entity>> &newEntities);
};
