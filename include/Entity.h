#include "math_utils.h"
#include "utils.h"
#include <SFML/Graphics.hpp>

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

class Entity {
  public:
    Vector2 position;
    float angle;

    Entity() {
        this->position = Vector2(0.0f, 0.0f);
        this->angle = 0.0f;
    }
    Entity(Vector2 position, float angle)
        : position(position), angle(angle) {}

  private:
};

class DrawableEntities : public sf::Drawable {
  public:
    DrawableEntities(const std::vector<Entity>& entities)
        : entities(entities) {}

    void update() {
        this->m_vertices = sf::VertexArray(sf::Triangles, 3 * entities.size());
        for (std::size_t i = 0; i < entities.size(); ++i) {
            const auto& entity = entities[i];
            auto rotatedPoint = rotate(entity.position.x, entity.position.y,
                                       entity.position.x - 10, entity.position.y + 10,
                                       entity.angle);
            m_vertices[3 * i + 0].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
            rotatedPoint = rotate(entity.position.x, entity.position.y, entity.position.x - 0,
                                  entity.position.y - 20,
                                  entity.angle);
            m_vertices[3 * i + 1].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
            rotatedPoint = rotate(entity.position.x, entity.position.y, entity.position.x + 10,
                                  entity.position.y + 10,
                                  entity.angle);
            m_vertices[3 * i + 2].position = sf::Vector2f(rotatedPoint.x, rotatedPoint.y);
            m_vertices[3 * i + 0].color = sf::Color::Red;
            m_vertices[3 * i + 1].color = sf::Color::Red;
            m_vertices[3 * i + 2].color = sf::Color::Red;
        }
    }

  private:
    const std::vector<Entity> entities;
    sf::VertexArray m_vertices;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // draw the vertex array
        target.draw(m_vertices, states);
    }
};

#endif
