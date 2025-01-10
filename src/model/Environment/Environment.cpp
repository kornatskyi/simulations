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

  physics->update(entities);

  std::vector<long unsigned int> toDelete;
  std::vector<std::shared_ptr<Entity>> newEntities;
  long unsigned int i{0};

  std::unordered_set<EntityPair> interacted;

  for (auto &entity : entities) {
    entity->moveForward(elapsedTime);
    auto collidingWith = physics->getPotentiallyColliding(entity);

    for (auto otherEntity : *collidingWith) {
      if (interacted.find(EntityPair(entity, otherEntity)) !=
          interacted.end()) {
        continue;
      }
      entity->interact(otherEntity);
      otherEntity->interact(entity);
      interacted.emplace(EntityPair(entity, otherEntity));
    }

    // Reproduction logic
    auto newEntity = entity->reproduce();
    if (newEntity != nullptr) {
      newEntities.push_back(newEntity);
    }
    // Collect dead entities
    if (!entity->alive()) {
      toDelete.push_back(i);

      // Convert dead Carnivores into Resources if they have energy
      if (entity->getEnergy() > 0 &&
          entity->getType() == EntityType::CARNIVORE) {
        auto newResourse = std::make_shared<Resource>(this);
        newResourse->setPosition(entity->getPosition())
            .setEnergy(entity->getEnergy());
        newEntities.push_back(newResourse);
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
  // auto newEntity = std::make_shared<Herbivore>(this);
  // newEntity->setPosition(Vector2(350, 500)).setSpeed(0);
  // entities.emplace_back(newEntity);

  std::mt19937 gen(42);
  std::uniform_int_distribution<> dist(-10, 10);
  std::uniform_int_distribution<> distAngle(0, 360);

  for (u_int i = 0; i < 50; ++i) {
    auto newEntity = std::make_shared<Herbivore>(this);
    newEntity->setPosition(Vector2(350 + dist(gen), 500 + dist(gen)))
        .setSpeed(10)
        .setAngle(60);
    entities.emplace_back(newEntity);
  }
}

// Randomly generate entities in the environment
void Environment::generateRandomEntities(u_int n) {
  std::mt19937 gen(42);
  std::uniform_int_distribution<> distX(0, Config::getInstance().width);
  std::uniform_int_distribution<> distY(0, Config::getInstance().width);
  std::uniform_int_distribution<> distAngle(0, 360);

  for (u_int i = 0; i < n; ++i) {
    Vector2 position(distX(gen), distY(gen));
    int angle = distAngle(gen);
    std::shared_ptr<Entity> newEntity;
    switch (i % 3) {
    case 0:
      newEntity = std::make_shared<Herbivore>(this);
      newEntity->setPosition(position).setAngle(angle);
      entities.emplace_back(newEntity);
      break;
    case 1:
      newEntity = std::make_shared<Carnivore>(this);
      newEntity->setPosition(position).setAngle(angle);
      entities.emplace_back(newEntity);
      break;
    case 2:
      newEntity = std::make_shared<Resource>(this);
      newEntity->setPosition(position).setAngle(angle).setSpeed(0);
      entities.emplace_back(newEntity);
      break;
    }
  }
}
