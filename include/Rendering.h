#ifndef RENDERING_HEADER
#define RENDERING_HEADER
#include "Carnivore.h"
#include "Entity.h"
#include "Herbivore.h"
#include "Resource.h"
#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

class EntityVertex {
  public:
  Entity &entity;
  sf::Color color;

  EntityVertex(Entity &entity, sf::Color color = sf::Color::Blue)
    : entity(entity), color(color) {}

  sf::VertexArray getVertices() {
    sf::VertexArray m_vertices = sf::VertexArray(sf::Triangles, 3);

    // Rotate
    sf::Vector2f entityPosition = convertToSFMLCoordinate(entity.position);
    auto rotatedPoint = rotate(
      entityPosition.x, entityPosition.y, entityPosition.x - entity.radius / 2,
      entityPosition.y + entity.radius / 2, -entity.angle);
    m_vertices[0].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
    rotatedPoint = rotate(entityPosition.x, entityPosition.y,
                          entityPosition.x - entity.radius / 2,
                          entityPosition.y - entity.radius / 2, -entity.angle);
    m_vertices[1].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
    rotatedPoint = rotate(entityPosition.x, entityPosition.y,
                          entityPosition.x + entity.radius,
                          entityPosition.y - 0, -entity.angle);
    m_vertices[2].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
    m_vertices[0].color = color;
    m_vertices[1].color = color;
    m_vertices[2].color = color;
    return m_vertices;
  }
};

class DrawableEntities : public sf::Drawable {
  public:
  std::vector<std::shared_ptr<Entity>> entities;

  DrawableEntities(std::vector<std::shared_ptr<Entity>> entities)
    : entities(entities) {}

  void update() {
    // VertexArray represents entities
    m_vertices = sf::VertexArray(sf::Triangles, 3 * entities.size());

    for (std::size_t i = 0; i < entities.size(); ++i) {
      auto &entity = entities[i];

      auto color = determineColor(*entity);

      sf::VertexArray tempVertices = EntityVertex(*entity, color).getVertices();
      m_vertices[i * 3 + 0] = tempVertices[0];
      m_vertices[i * 3 + 1] = tempVertices[1];
      m_vertices[i * 3 + 2] = tempVertices[2];
    }
  }

  sf::Color determineColor(const Entity &entity) {

    switch (entity.type) {
    case EntityType::ENTITY:
      return sf::Color::White;
    case EntityType::CARNIVORE:
      return sf::Color::Red;
    case EntityType::HERBIVORE:
      return sf::Color::Blue;
    case EntityType::RESOURCE:
      return sf::Color::Green;
    default:
      return sf::Color::Magenta;
    }
  }

  private:
  sf::VertexArray m_vertices;
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    // draw the vertex array
    target.draw(m_vertices, states);

    if (Config::drawBoundary) {
      for (auto entity : entities) {

        sf::Vector2f entityPosition = convertToSFMLCoordinate(entity->position);
        sf::CircleShape circle(entity->radius);
        circle.setPosition(sf::Vector2f(entityPosition.x - entity->radius,
                                        entityPosition.y - entity->radius));
        circle.setFillColor(sf::Color::Transparent); // Make inside transparent
        circle.setOutlineThickness(1);

        circle.setOutlineColor(sf::Color::Red);
        target.draw(circle);

        // Draw entity center
        sf::CircleShape center(2);
        center.setPosition(sf::Vector2f(entityPosition.x - center.getRadius(),
                                        entityPosition.y - center.getRadius()));
        center.setFillColor(sf::Color::Red);
        target.draw(center);
      }
    }
  }
};
#endif