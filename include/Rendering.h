#ifndef RENDERING_HEADER
#define RENDERING_HEADER

#include "Carnivore.h"
#include "Entity.h"
#include "Herbivore.h"
#include "Resource.h"
#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class EntityRenderer {
  public:
  static sf::VertexArray
  createEntityShape(const std::shared_ptr<Entity> &entity,
                    const sf::Color &color) {
    sf::VertexArray vertices(sf::Triangles, 3);

    // Generate entity's triangle representation
    sf::Vector2f position = convertToSFMLCoordinate(entity->position);
    std::array<sf::Vector2f, 3> points = {
      rotatePointAround(position,
                        sf::Vector2f(position.x - entity->radius / 2,
                                     position.y + entity->radius / 2),
                        -entity->angle),
      rotatePointAround(position,
                        sf::Vector2f(position.x - entity->radius / 2,
                                     position.y - entity->radius / 2),
                        -entity->angle),
      rotatePointAround(position,
                        sf::Vector2f(position.x + entity->radius, position.y),
                        -entity->angle)};

    for (int i = 0; i < 3; ++i) {
      vertices[i].position = points[i];
      vertices[i].color = color;
    }

    return vertices;
  }

  static sf::Color determineColor(EntityType type) {
    switch (type) {
    case EntityType::CARNIVORE:
      return sf::Color::Red;
    case EntityType::HERBIVORE:
      return sf::Color::Green;
    case EntityType::RESOURCE:
      return sf::Color::Blue;
    default:
      return sf::Color::White;
    }
  }
};

class DrawableEntities : public sf::Drawable {
  private:
  std::vector<std::shared_ptr<Entity>> entities;
  mutable sf::VertexArray m_vertices;
  bool boundaryEnabled = Config::drawBoundary;

  void updateVertices() const {
    m_vertices.clear();
    m_vertices.setPrimitiveType(sf::Triangles);

    for (const auto &entity : entities) {
      sf::VertexArray shape = EntityRenderer::createEntityShape(
        entity, EntityRenderer::determineColor(entity->getType()));
      for (std::size_t i = 0; i < shape.getVertexCount(); ++i) {
        m_vertices.append(shape[i]);
      }
    }
  }

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
      boundary.setOutlineColor(sf::Color::Red);
      target.draw(boundary, states);

      // Draw entity center
      sf::CircleShape center(2);
      center.setPosition(position.x - 2, position.y - 2);
      center.setFillColor(sf::Color::Red);
      target.draw(center, states);
    }
  }

  public:
  explicit DrawableEntities(
    const std::vector<std::shared_ptr<Entity>> &entities)
    : entities(entities), m_vertices(sf::Triangles) {}

  void setBoundaryEnabled(bool enabled) { boundaryEnabled = enabled; }

  protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    updateVertices();
    target.draw(m_vertices, states);
    drawBoundaries(target, states);
  }
};

#endif
