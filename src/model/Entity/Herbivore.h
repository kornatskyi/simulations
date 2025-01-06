#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Entity.h"

class Herbivore : public Entity {
public:
  Herbivore(Environment *env = nullptr);
  void interact(std::shared_ptr<Entity> other) override;
  std::shared_ptr<Entity> reproduce() override;
  EntityType getType() const override;
  void die() override;
};
