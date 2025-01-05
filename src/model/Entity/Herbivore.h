#ifndef HERBIVORE_HEADER
#define HERBIVORE_HEADER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Entity.h"

class Herbivore : public Entity {
public:
  using Entity::Entity; // Inherit constructors from Entity

  Herbivore(Vector2 position, float speed, float angle, float radius,
            float energy, Environment *env = nullptr);

  virtual void die() override;
  virtual EntityType getType() const override;
  virtual void interact(std::shared_ptr<Entity> other) override;
  virtual std::shared_ptr<Entity> reproduce() override;
};

#endif // HERBIVORE_HEADER
