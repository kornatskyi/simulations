#ifndef CARNIVORE_HEADER
#define CARNIVORE_HEADER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Entity.h"

class Carnivore : public Entity {
public:
  using Entity::Entity; // Inherit constructors from Entity

  Carnivore(Vector2 position, float speed, float angle, float radius,
            float energy, Environment *env = nullptr);

  virtual void die() override;
  virtual void interact(std::shared_ptr<Entity> other) override;
  void moveForward(float elapsedTime) override;
  virtual EntityType getType() const override;
  virtual std::shared_ptr<Entity> reproduce() override;
};

#endif // CARNIVORE_HEADER
