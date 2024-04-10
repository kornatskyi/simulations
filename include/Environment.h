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
#include <vector>

class Environment {
  public:
  std::vector<std::shared_ptr<Entity>> entities;
  Physics physics;
  Environment() {
    // physics = Physics();
    std::shared_ptr<Entity> entity =
      std::make_shared<Entity>(Entity(Vector2(140, 140), 200, 90));
    std::shared_ptr<Entity> entity2 =
      std::make_shared<Herbivore>(Herbivore(Vector2(150, 150), 200, 45));
    std::shared_ptr<Entity> entity3 =
      std::make_shared<Resource>(Resource(Vector2(500, 700), 200, 180));
    std::shared_ptr<Entity> entity4 =
      std::make_shared<Carnivore>(Carnivore(Vector2(600, 700), 200, 360));
    std::shared_ptr<Entity> entity5 =
      std::make_shared<Entity>(Entity(Vector2(300, 800), 200, 270));
    std::shared_ptr<Entity> entity6 =
      std::make_shared<Entity>(Entity(Vector2(400, 800), 200, 30));
    entities = {
      entity, entity2, entity3, entity4, entity5, entity6,
    };
  }

  /// @brief Constructor which generates `n` Entities with random
  /// characteristics
  /// @param n - number of Entities to generate
  Environment(u_int n) {
    // physics = Physics();
    entities = generateEntities(n);
    // auto herbs = generateHerbivores(n);
    // entities.insert(entities.end(), herbs.begin(), herbs.end());
  }

  void update(float elapsedTime) {
    // Move
    // for (auto entity : entities) {
    //   entity->moveForward(elapsedTime);
    // }

    auto collidingEntities = physics.collidingEntities(entities);

    for (auto const &t : collidingEntities) {
      std::cout << std::get<0>(t)->getLabel() + " and " +
                     std::get<1>(t)->getLabel() + " are colliding!"
                << std::endl;
    }
  }

  private:
  std::vector<std::shared_ptr<Entity>> generateEntities(u_int n) {
    srand(Config::defaultSeed);
    std::vector<std::shared_ptr<Entity>> entities{};
    for (u_int i = 0; i < n; i++) {
      auto position = Vector2(rand() % Config::WIDTH, rand() % Config::HEIGHT);
      entities.push_back(
        std::make_shared<Herbivore>(Herbivore(position, 70, rand() % 360)));
    }

    return entities;
  }
  std::vector<Herbivore> generateHerbivores(u_int n) {
    srand(Config::defaultSeed + 1);
    std::vector<Herbivore> entities{};
    for (u_int i = 0; i < n; i++) {
      auto position = Vector2(rand() % Config::WIDTH, rand() % Config::HEIGHT);
      entities.push_back(Herbivore(position, 70, rand() % 360));
    }

    return entities;
  }
};

#endif
