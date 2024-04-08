#ifndef ENVIRONMENT_HEADER
#define ENVIRONMENT_HEADER
#include "Physics.h"
#include "math_utils.h"
#include "utils.h"
#include <iostream>
#include <vector>

class Environment {
  public:
  std::vector<Entity> entities;
  Physics physics;
  Environment() {
    // physics = Physics();
    Entity entity(Vector2(140, 140), 200, 90);
    Entity entity2(Vector2(150, 150), 200, 45);
    Entity entity3(Vector2(500, 700), 200, 180);
    Entity entity4(Vector2(600, 700), 200, 360);
    Entity entity5(Vector2(300, 800), 200, 270);
    Entity entity6(Vector2(400, 800), 200, 30);
    entities = std::vector<Entity>{
      entity, entity2, entity3, entity4, entity5, entity6,
    };
  }

  /// @brief Constructor which generates `n` Entities with random
  /// characteristics
  /// @param n - number of Entities to generate
  Environment(u_int n) {
    // physics = Physics();
    entities = generateEntities(n);
  }

  void update() {

    auto collidingEntities = physics.collidingEntities(entities);

    for (auto const &t : collidingEntities) {
      std::cout << std::get<0>(t).getLabel() + " and " +
                     std::get<1>(t).getLabel() + " are colliding!"
                << std::endl;
    }
  }

  private:
  std::vector<Entity> generateEntities(u_int n) {
    srand(Config::defaultSeed);
    std::vector<Entity> entities{};
    for (u_int i = 0; i < n; i++) {
      auto position = Vector2(rand() % Config::WIDTH, rand() % Config::HEIGHT);
      entities.push_back(Entity(position, 70, rand() % 360));
    }

    return entities;
  }
};

#endif
