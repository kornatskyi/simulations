#include "Carnivore.h"

// Constructor
Carnivore::Carnivore(Environment *env) : Entity(env) {
  type = EntityType::CARNIVORE;
}

// Die method
void Carnivore::die() { isAlive = false; }

// Interaction with other entities
void Carnivore::interact(std::shared_ptr<Entity> other) {
  if (other->getType() == EntityType::HERBIVORE) {
    other->die();
    energy += other->getEnergy();
  }
}

// Movement logic with lifetime check
void Carnivore::moveForward(float elapsedTime) {
  Entity::moveForward(elapsedTime);
  lifetime -= elapsedTime;
  if (lifetime <= 0) {
    die();
  }
}

// Return the type of entity (Carnivore)
EntityType Carnivore::getType() const { return EntityType::CARNIVORE; }

// Reproduction logic
std::shared_ptr<Entity> Carnivore::reproduce() {
  if (energy > EnvConfig::getInstance().energyToSplit) {
    energy -= EnvConfig::getInstance().energyToSplit;

    auto newEntity = std::make_shared<Carnivore>(env);
    newEntity->setPosition(position);
    return newEntity;
  }
  return nullptr;
}
