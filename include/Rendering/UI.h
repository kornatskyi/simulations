#ifndef UI_HEADER
#define UI_HEADER

#include "../Environement/Environment.h"
#include <SFML/Graphics.hpp>
#include <memory>

class UI : public sf::Drawable {
  public:
  UI(std::shared_ptr<Environment> env) : env(env) {
    if (!font.loadFromFile("assets/3270-Medium Nerd Font Complete Mono.ttf")) {
      throw std::runtime_error("Failed to load font");
    }
    entitiesCount = initText();
    totalEnergy = initText();
  }

  protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    // Update the string only
    entitiesCount.setString("Entities: " +
                            std::to_string(env->entities.size()));
    entitiesCount.setPosition(10, 10);
    totalEnergy.setString(
      "Energy: " +
      std::to_string(std::accumulate(
        env->entities.begin(), env->entities.end(), 0.0f,
        [](float sum, const auto &e) { return sum + e->energy; })));
    totalEnergy.setPosition(10, 35);

    target.draw(entitiesCount, states);
    target.draw(totalEnergy, states);
  }

  private:
  sf::Text initText() {
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    return text;
  }
  std::shared_ptr<Environment> env;
  sf::Font font;
  mutable sf::Text entitiesCount;
  mutable sf::Text totalEnergy;
};

#endif
