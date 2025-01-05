#pragma once

#include "model/Entity/Entity.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class DrawableEntities : public sf::Drawable {
private:
  const std::vector<std::shared_ptr<Entity>> &entities;
  mutable std::vector<sf::VertexArray> shapesToRender;
  bool boundaryEnabled;

  void drawBoundaries(sf::RenderTarget &target, sf::RenderStates states) const;
  void updateShapes() const;

public:
  explicit DrawableEntities(
      const std::vector<std::shared_ptr<Entity>> &entities);
  void setBoundaryEnabled(bool enabled);

protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};
