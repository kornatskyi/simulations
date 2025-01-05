#include "Resource.h"

// Constructor
Resource::Resource(Vector2 position, float speed, float angle, float radius,
                   float energy, Environment *env)
    : Entity(position, 0, angle, radius, energy, env) {
  type = EntityType::RESOURCE;
}

// Die method
void Resource::die() { isAlive = false; }

// Return the type of entity (Resource)
EntityType Resource::getType() const { return EntityType::RESOURCE; }

// Interaction with other entities (no interaction for Resource)
void Resource::interact(std::shared_ptr<Entity> other) { return; }

// Reproduction logic (Resource does not reproduce)
std::shared_ptr<Entity> Resource::reproduce() { return nullptr; }
