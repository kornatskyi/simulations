#include "model/Environment/Environment.h"
#include <Config.h>
#include <EnvConfig.h>
#include <model/Entity/Carnivore.h>
#include <model/Entity/Entity.h>
#include <model/Entity/Herbivore.h>
#include <model/Entity/Resource.h>
#include <model/Physics/Physics.h>

// Default constructor
Environment::Environment() : physics(std::make_shared<Physics>()) {
  initializeDefaultEntities();
}

// Constructor with random entity generation
Environment::Environment(u_int n) : physics(std::make_shared<Physics>()) {
  generateRandomEntities(n);
}

// Update function to handle entity movement, interaction, and reproduction
void Environment::update(float elapsedTime) {
  for (auto &entity : entities) {
    entity->moveForward(elapsedTime);
  }

  auto collidingPairs = physics->getCollidingEntities(entities);
  for (const auto &[first, second] : collidingPairs) {
    first->interact(second);
    second->interact(first);
  }

  std::vector<long unsigned int> toDelete;
  std::vector<std::shared_ptr<Entity>> newEntities;
  long unsigned int i{0};

  for (auto &entity : entities) {
    // Reproduction logic
    auto newEntity = entity->reproduce();
    if (newEntity != nullptr) {
      newEntities.push_back(newEntity);
    }

    // Collect dead entities
    if (!entity->isAlive) {
      toDelete.push_back(i);

      // Convert dead Carnivores into Resources if they have energy
      if (entity->energy > 0 && entity->type == EntityType::CARNIVORE) {
        newEntities.push_back(std::make_shared<Resource>(
            entity->position, 0.f, 0.f, 20.f, entity->energy, this));
      }
    }
    i++;
  }

  // Remove entities in reverse order to avoid invalidating iterators
  std::reverse(toDelete.begin(), toDelete.end());
  for (auto j : toDelete) {
    if (j < entities.size()) {
      entities.erase(entities.begin() + j);
    }
  }

  // Add new entities to the list
  entities.insert(entities.end(), newEntities.begin(), newEntities.end());
}

// Initialize entities by default
void Environment::initializeDefaultEntities() {
  entities.emplace_back(
      std::make_shared<Herbivore>(Vector2(10, 50), 200, 0, 10, 0));
  entities.emplace_back(
      std::make_shared<Resource>(Vector2(50, 50), 200, 45, 10, 0));
  // Additional entities can be uncommented as needed
  // entities.emplace_back(std::make_shared<Resource>(Vector2(500, 700), 200,
  // 180, 20, 0));
  // entities.emplace_back(std::make_shared<Carnivore>(Vector2(600, 700), 200,
  // 360, 20, 0));
}

// Randomly generate entities in the environment
void Environment::generateRandomEntities(u_int n) {
  std::mt19937 gen(42);
  std::uniform_int_distribution<> distX(0, Config::WIDTH);
  std::uniform_int_distribution<> distY(0, Config::HEIGHT);
  std::uniform_int_distribution<> distAngle(0, 360);

  for (u_int i = 0; i < n; ++i) {
    Vector2 position(distX(gen), distY(gen));
    int angle = distAngle(gen);

    switch (i % 3) {
    case 0:
      entities.emplace_back(std::make_shared<Herbivore>(
          position, EnvConfig::entitySpeed, angle, EnvConfig::entityRadius,
          EnvConfig::entityEnergy));
      break;
    case 1:
      entities.emplace_back(std::make_shared<Carnivore>(
          position, EnvConfig::entitySpeed, angle, EnvConfig::entityRadius,
          EnvConfig::entityEnergy));
      break;
    case 2:
      entities.emplace_back(std::make_shared<Resource>(
          position, EnvConfig::entitySpeed, angle, EnvConfig::entityRadius,
          EnvConfig::entityEnergy));
      break;
    }
  }
}
