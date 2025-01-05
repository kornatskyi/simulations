#include "Carnivore.h"

// Constructor
Carnivore::Carnivore(Vector2 position, float speed, float angle, float radius,
                     float energy, Environment *env)
    : Entity(position, speed, angle, radius, energy, env) {
  type = EntityType::CARNIVORE;
  lifetime = 10;
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
  const float energyToSplit = 10;
  if (energy > energyToSplit) {
    energy -= energyToSplit;
    return std::make_shared<Carnivore>(position, speed, angle - 180, radius,
                                       energyToSplit, env);
  }
  return nullptr;
}
