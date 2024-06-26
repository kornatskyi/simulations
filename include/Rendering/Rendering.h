#ifndef RENDERING_HEADER
#define RENDERING_HEADER

#include "../Environement/Carnivore.h"
#include "../Environement/Entity.h"
#include "../Environement/Herbivore.h"
#include "../Environement/Resource.h"
#include "../Physics/Physics.h"
#include "../utils/math_utils.h"
#include "../utils/utils.h"
#include "DrawablePhysics.h"
#include "EntityRenderer.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class DrawableEntities : public sf::Drawable {
  private:
  const std::vector<std::shared_ptr<Entity>> &entities;
  mutable std::vector<sf::VertexArray> m_shapes; // Store individual shapes
  bool boundaryEnabled = Config::drawBoundary;

  void drawBoundaries(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!boundaryEnabled)
      return;

    for (const auto &entity : entities) {
      sf::Vector2f position = convertToSFMLCoordinate(entity->position);

      // Draw boundary
      sf::CircleShape boundary(entity->radius);
      boundary.setPosition(position.x - entity->radius,
                           position.y - entity->radius);
      boundary.setFillColor(sf::Color::Transparent);
      boundary.setOutlineThickness(1);
      boundary.setOutlineColor(sf::Color::White);
      target.draw(boundary, states);

      // Draw entity center
      sf::CircleShape center(2);
      center.setPosition(position.x - 2, position.y - 2);
      center.setFillColor(sf::Color::White);
      target.draw(center, states);
    }
  }

  void updateShapes() const {
    m_shapes.clear();
    for (const auto &entity : entities) {
      m_shapes.push_back(EntityRenderer::createShape(
        entity, EntityRenderer::determineColor(entity->getType())));
    }
  }

  public:
  explicit DrawableEntities(
    const std::vector<std::shared_ptr<Entity>> &entities)
    : entities(entities) {}

  void setBoundaryEnabled(bool enabled) { boundaryEnabled = enabled; }

  protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    updateShapes();

    for (const auto &shape : m_shapes) {
      target.draw(shape, states);
    }

    if (boundaryEnabled) {
      drawBoundaries(target, states);
    }
  }
};

#endif
