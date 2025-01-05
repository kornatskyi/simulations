#pragma once

#include "model/Physics/Physics.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

class Environment {
public:
  std::vector<std::shared_ptr<Entity>> entities;
  std::shared_ptr<Physics> physics;

  explicit Environment();
  explicit Environment(u_int n);

  void update(float elapsedTime);

private:
  void initializeDefaultEntities();
  void generateRandomEntities(u_int n);
};
