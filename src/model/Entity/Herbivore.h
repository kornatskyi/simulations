#ifndef HERBIVORE_HEADER
#define HERBIVORE_HEADER

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Entity.h"

class Herbivore : public Entity {
public:
  Herbivore(Vector2 position, float speed, float angle, float radius,
            float energy, Environment *env = nullptr);
  void interact(std::shared_ptr<Entity> other) override;
  std::shared_ptr<Entity> reproduce() override;
  EntityType getType() const override;
  void die() override;
};

#endif // HERBIVORE_HEADER
