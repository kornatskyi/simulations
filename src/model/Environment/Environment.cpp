#include "model/Environment/Environment.h"
#include <Config.h>
#include <model/Entity/Carnivore.h>
#include <model/Entity/Entity.h>
#include <model/Entity/Herbivore.h>
#include <model/Entity/Resource.h>
#include <model/Physics/Physics.h>

Environment::Environment()
    : physics(std::make_shared<Physics>()),
      randomEngine(std::random_device{}()) // or fixed seed for deterministic
{
  initializeDefaultEntities();
}

Environment::Environment(unsigned int n)
    : physics(std::make_shared<Physics>()),
      randomEngine(std::random_device{}()) {
  generateRandomEntities(n);
}
void Environment::update(float elapsedTime) {
  // 1. Update physics (broad-phase, velocity, etc.)
  physics->update(entities);

  // 2. Move each entity
  moveEntities(elapsedTime);

  // 3. Handle collisions (pairs, interactions)
  handleCollisions();

  // 4. Handle reproduction
  std::vector<std::shared_ptr<Entity>> newEntities;
  handleReproduction(newEntities);

  // 5. Handle deaths, including carnivores => resources
  handleDeathsAndConversions(newEntities);

  // 6. Insert new entities
  entities.insert(entities.end(), newEntities.begin(), newEntities.end());
}

void Environment::moveEntities(float elapsedTime) {
  for (auto &entity : entities) {
    entity->moveForward(elapsedTime);
  }
}

void Environment::handleCollisions() {
  std::unordered_set<EntityPair> interacted;

  auto pairs = physics->getAllCollidingPairs();

  for (auto &pair : pairs) {
    auto [e1, e2] = pair;
    if (interacted.find(pair) != interacted.end()) {
      continue;
    }

    if (physics->areColliding(e1, e2)) {
      // Two-way interaction
      e1->interact(e2);
      e2->interact(e1);

      
      
    }

    // Mark these two as having interacted
    // interacted.insert(pair);
  }
}

void Environment::handleReproduction(
    std::vector<std::shared_ptr<Entity>> &newEntities) {
  for (auto &entity : entities) {
    auto offspring = entity->reproduce();
    if (offspring) {
      newEntities.push_back(offspring);
    }
  }
}

void Environment::handleDeathsAndConversions(
    std::vector<std::shared_ptr<Entity>> &newEntities) {
  // Instead of tracking indices, use remove-if
  auto it = std::remove_if(
      entities.begin(), entities.end(), [&](const std::shared_ptr<Entity> &e) {
        if (!e->alive()) {
          // If carnivore with > 0 energy => resource
          if (e->getType() == EntityType::CARNIVORE && e->getEnergy() > 0) {
            auto newResource = std::make_shared<Resource>(this);
            newResource->setPosition(e->getPosition())
                .setEnergy(e->getEnergy());
            newEntities.push_back(newResource);
          }
          return true; // remove this entity
        }
        return false; // keep it
      });
  entities.erase(it, entities.end());
}

void Environment::initializeDefaultEntities() {
  std::uniform_int_distribution<> dist(-10, 10);
  // Possibly also uniform_int_distribution<> distAngle(0, 360);

  for (unsigned int i = 0; i < 50; ++i) {
    auto herb = std::make_shared<Herbivore>(this);
    herb->setPosition(
            Vector2(350 + dist(randomEngine), 500 + dist(randomEngine)))
        .setSpeed(10)
        .setAngle(60);
    entities.push_back(herb);
  }
}

void Environment::generateRandomEntities(unsigned int n) {
  std::uniform_int_distribution<> distX(0, Config::getInstance().width);
  std::uniform_int_distribution<> distY(0, Config::getInstance().height);
  std::uniform_int_distribution<> distAngle(0, 360);
  std::uniform_real_distribution<> randDist(0, 1);

  for (unsigned int i = 0; i < n; ++i) {
    Vector2 position(distX(randomEngine), distY(randomEngine));
    int angle = distAngle(randomEngine);
    float rand = randDist(randomEngine);

    std::shared_ptr<Entity> newEntity;
    if (rand > 0.4) {
      newEntity = std::make_shared<Herbivore>(this);
      newEntity->setPosition(position).setAngle(angle);
    } else if (rand > 0.33) {
      newEntity = std::make_shared<Carnivore>(this);
      newEntity->setPosition(position).setAngle(angle);
    } else {
      newEntity = std::make_shared<Resource>(this);
      newEntity->setPosition(position).setAngle(angle).setSpeed(0);
    }
    entities.push_back(newEntity);
  }
}
