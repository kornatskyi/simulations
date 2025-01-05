#ifndef RESOURCE_HEADER
#define RESOURCE_HEADER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Entity.h"

class Resource : public Entity {
public:
  using Entity::Entity; // Inherit constructors from Entity

  Resource(Vector2 position, float speed, float angle, float radius,
           float energy, Environment *env = nullptr);

  virtual void die() override;
  virtual EntityType getType() const override;
  virtual void interact(std::shared_ptr<Entity> other) override;
  virtual std::shared_ptr<Entity> reproduce() override;
};

#endif // RESOURCE_HEADER
