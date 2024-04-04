#include <SFML/Graphics.hpp>

#ifndef ENTITY_HEADER
#define ENTITY_HEADER

struct Vector2 {
    float x;
    float y;
    Vector2() = default;
    Vector2(float x, float y)
        : x(x), y(y) {}
};

class Entity {
  public:
    Vector2 position;
    float angle;

    Entity() {
        this->position = Vector2(0.0f, 0.0f);
    }
    Entity(Vector2 position) {
        this->position = position;
    }

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
            m_vertices[3 * i + 0].position = sf::Vector2f(entity.position.x - 10, entity.position.y + 10);
            m_vertices[3 * i + 1].position = sf::Vector2f(entity.position.x - 0, entity.position.y - 20);
            m_vertices[3 * i + 2].position = sf::Vector2f(entity.position.x + 10, entity.position.y + 10);
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
