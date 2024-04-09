#ifndef RENDERING_HEADER
#define RENDERING_HEADER
#include "../include/Entity.h"
#include "../include/math_utils.h"
#include "../include/utils.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

class DrawableEntities : public sf::Drawable {
  public:
  std::vector<Entity> &entities;

  DrawableEntities(std::vector<Entity> &entities) : entities(entities) {}

  void update() {
    // VertexArray represents entities
    this->m_vertices = sf::VertexArray(sf::Triangles, 3 * entities.size());
    for (std::size_t i = 0; i < entities.size(); ++i) {
      auto &entity = entities[i];

      // Rotate
      sf::Vector2f entityPosition = convertToSFMLCoordinate(entity.position);
      auto rotatedPoint =
        rotate(entityPosition.x, entityPosition.y,
               entityPosition.x - entity.radius / 2,
               entityPosition.y + entity.radius / 2, -entity.angle);
      m_vertices[3 * i + 0].position =
        sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
      rotatedPoint =
        rotate(entityPosition.x, entityPosition.y,
               entityPosition.x - entity.radius / 2,
               entityPosition.y - entity.radius / 2, -entity.angle);
      m_vertices[3 * i + 1].position =
        sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
      rotatedPoint = rotate(entityPosition.x, entityPosition.y,
                            entityPosition.x + entity.radius,
                            entityPosition.y - 0, -entity.angle);
      m_vertices[3 * i + 2].position =
        sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
      m_vertices[3 * i + 0].color = sf::Color::Blue;
      m_vertices[3 * i + 1].color = sf::Color::Blue;
      m_vertices[3 * i + 2].color = sf::Color::Blue;
    }
  }

  private:
  sf::VertexArray m_vertices;
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    // draw the vertex array
    target.draw(m_vertices, states);

    if (Config::drawBoundary) {
      for (auto &entity : entities) {

        sf::Vector2f entityPosition = convertToSFMLCoordinate(entity.position);
        sf::CircleShape circle(entity.radius);
        circle.setPosition(sf::Vector2f(entityPosition.x - entity.radius,
                                        entityPosition.y - entity.radius));
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