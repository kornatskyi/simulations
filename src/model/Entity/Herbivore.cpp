#include "Herbivore.h"

// Constructor
Herbivore::Herbivore(Vector2 position, float speed, float angle, float radius,
                     float energy, Environment *env)
    : Entity(position, speed, angle, radius, energy, env) {
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
    energy += other->energy;
  }
}

// Reproduction logic
std::shared_ptr<Entity> Herbivore::reproduce() {
  const float energyToSplit = 10;
  if (energy > energyToSplit) {
    energy -= energyToSplit;
    return std::make_shared<Herbivore>(position, speed, angle + 180, radius,
                                       energyToSplit, env);
  }
  return nullptr;
}
