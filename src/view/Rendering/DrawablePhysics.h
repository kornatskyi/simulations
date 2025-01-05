#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <model/Physics/Physics.h>
#include <vector>

class DrawablePhysics : public sf::Drawable {
public:
  explicit DrawablePhysics(std::shared_ptr<Physics> physics);
  std::shared_ptr<Physics> physics;

protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};