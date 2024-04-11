#ifndef RENDERING_HEADER
#define RENDERING_HEADER

#include "Carnivore.h"
#include "Entity.h"
#include "Herbivore.h"
#include "Physics.h"
#include "Resource.h"
#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class EntityRenderer {
  public:
  static sf::VertexArray createShape(const std::shared_ptr<Entity> &entity,
                                     const sf::Color &color) {
    switch (entity->getType()) {
    case EntityType::RESOURCE:
      return createRectangleShape(std::static_pointer_cast<Resource>(entity),
                                  color);
    default:
      return createTriangleShape(entity, color);
    }
  }

  static sf::Color determineColor(EntityType type) {
    switch (type) {
    case EntityType::CARNIVORE:
      return sf::Color::Red;
    case EntityType::HERBIVORE:
      return sf::Color::Blue;
    case EntityType::RESOURCE:
      return sf::Color::Green;
    default:
      return sf::Color::White;
    }
  }

  private:
  static sf::VertexArray
  createTriangleShape(const std::shared_ptr<Entity> &entity,
                      const sf::Color &color) {
    sf::VertexArray vertices(sf::Triangles, 3);
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

  static sf::VertexArray
  createRectangleShape(const std::shared_ptr<Resource> &entity,
                       const sf::Color &color) {
    sf::VertexArray vertices(sf::Quads, 4);
    sf::Vector2f position = convertToSFMLCoordinate(entity->position);
    float size =
      entity
        ->radius; // Assuming radius is used to determine the size of the square

    vertices[0].position = position + sf::Vector2f(-size / 2, -size / 2);
    vertices[1].position = position + sf::Vector2f(size / 2, -size / 2);
    vertices[2].position = position + sf::Vector2f(size / 2, size / 2);
    vertices[3].position = position + sf::Vector2f(-size / 2, size / 2);

    for (int i = 0; i < 4; ++i) {
      vertices[i].color = color;
    }

    return vertices;
  }
};

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

class DrawablePhysics : public sf::Drawable {
  public:
  std::shared_ptr<Physics> physics;
  DrawablePhysics(std::shared_ptr<Physics> physics) : physics(physics) {}

  private:
  protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    auto cells = physics->getCells();
    for (auto &[x, y] : cells) {
      auto rect = sf::RectangleShape(
        sf::Vector2f(physics->getCellSize(), physics->getCellSize()));
      rect.setPosition(x, y);
      rect.setOutlineColor(sf::Color::Red);
      rect.setFillColor(sf::Color::Transparent);
      rect.setOutlineThickness(1);
      target.draw(rect, states);
    }
  }
};

#endif
