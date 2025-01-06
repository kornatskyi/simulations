#include "Herbivore.h"

// Constructor
Herbivore::Herbivore(Environment *env) : Entity(env) {
  type = EntityType::HERBIVORE;
}

// Die method
void Herbivore::die() { isAlive = false; }

// Return the type of entity (Herbivore)
EntityType Herbivore::getType() const { return EntityType::HERBIVORE; }

// Interaction with other entities
void Herbivore::interact(std::shared_ptr<Entity> other) {
  if (other->getType() == EntityType::RESOURCE) {
    other->die();
    energy += other->getEnergy();
  }
}

// Reproduction logic
std::shared_ptr<Entity> Herbivore::reproduce() {
  if (energy > EnvConfig::getInstance().energyToSplit) {
    energy -= EnvConfig::getInstance().energyToSplit;
    auto newEntity = std::make_shared<Herbivore>(env);
    newEntity->setPosition(position);
    return newEntity;
  }
  return nullptr;
}
