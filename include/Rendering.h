#include "../include/Entity.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#ifndef RENDERING_HEADER
#define RENDERING_HEADER

class DrawableEntities : public sf::Drawable {
  public:
  DrawableEntities(std::vector<Entity> &entities) : entities(entities) {}

  void update(float elapsedTime) {
    this->m_vertices = sf::VertexArray(sf::Triangles, 3 * entities.size());
    for (std::size_t i = 0; i < entities.size(); ++i) {
      auto &entity = entities[i];
      // Move
      entity.moveForward(elapsedTime);

      // Rotate
      sf::Vector2f entityPosition = convertToSFMLCoordinate(entity.position);
      auto rotatedPoint =
        rotate(entityPosition.x, entityPosition.y, entityPosition.x - 10,
               entityPosition.y + 10, -entity.angle);
      m_vertices[3 * i + 0].position =
        sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
      rotatedPoint =
        rotate(entityPosition.x, entityPosition.y, entityPosition.x - 10,
               entityPosition.y - 10, -entity.angle);
      m_vertices[3 * i + 1].position =
        sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
      rotatedPoint =
        rotate(entityPosition.x, entityPosition.y, entityPosition.x + 20,
               entityPosition.y - 0, -entity.angle);
      m_vertices[3 * i + 2].position =
        sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
      m_vertices[3 * i + 0].color = sf::Color::Red;
      m_vertices[3 * i + 1].color = sf::Color::Red;
      m_vertices[3 * i + 2].color = sf::Color::Red;
    }
  }

  private:
  std::vector<Entity> entities;
  sf::VertexArray m_vertices;
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // draw the vertex array
    target.draw(m_vertices, states);
  }
};

#endif