#ifndef ENVIRONMENT_HEADER
#define ENVIRONMENT_HEADER

#include "Carnivore.h"
#include "Entity.h"
#include "Herbivore.h"
#include "Physics.h"
#include "Resource.h"
#include "math_utils.h"
#include "utils.h"
#include <iostream>
#include <memory>
#include <random>
#include <vector>

class Environment {
  public:
  std::vector<std::shared_ptr<Entity>> entities;
  Physics physics;

  explicit Environment() { initializeDefaultEntities(); }

  explicit Environment(u_int n) { generateRandomEntities(n); }

  void update(float elapsedTime) {
    for (auto &entity : entities) {
      entity->moveForward(elapsedTime);
    }

    auto collidingPairs = physics.collidingEntities(entities);
    for (const auto &[first, second] : collidingPairs) {
      first->interact(second);
      second->interact(first);
    }

    std::vector<long unsigned int> toDelete;
    long unsigned int i{0};
    for (auto &entity : entities) {
      if (!entity->isAlive) {
        toDelete.push_back(i);
      }
      i++;
    }
    for (auto j : toDelete) {
      if (j < entities.size()) {
        entities.erase(entities.begin() + j);
      }
    }
  }

  private:
  void initializeDefaultEntities() {
    entities.emplace_back(
      std::make_shared<Herbivore>(Vector2(10, 50), 200, 0, 10, 0));
    entities.emplace_back(
      std::make_shared<Resource>(Vector2(50, 50), 200, 45, 10, 0));
    // entities.emplace_back(
    //   std::make_shared<Resource>(Vector2(500, 700), 200, 180, 20, 0));
    // entities.emplace_back(
    //   std::make_shared<Carnivore>(Vector2(600, 700), 200, 360, 20, 0));
    // entities.emplace_back(
    //   std::make_shared<Entity>(Vector2(300, 800), 200, 270, 20, 0));
    // entities.emplace_back(
    //   std::make_shared<Entity>(Vector2(400, 800), 200, 30, 20, 0));
  }

  void generateRandomEntities(u_int n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distX(0, Config::WIDTH);
    std::uniform_int_distribution<> distY(0, Config::HEIGHT);
    std::uniform_int_distribution<> distAngle(0, 360);

    for (u_int i = 0; i < n; ++i) {
      Vector2 position(distX(gen), distY(gen));
      int angle = distAngle(gen);
      // Randomly choose the type of entity to create
      switch (i % 3) {
      case 0:
        entities.emplace_back(
          std::make_shared<Herbivore>(position, 70, angle, 20, 0));
        break;
      case 1:
        entities.emplace_back(
          std::make_shared<Carnivore>(position, 70, angle, 20, 0));
        break;
      case 2:
        entities.emplace_back(
          std::make_shared<Resource>(position, 70, angle, 20, 0));
        break;
      }
    }
  }
};

#endif
