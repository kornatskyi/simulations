#include "UI.h"
#include <model/Environment/Environment.h>

// Constructor
UI::UI(std::shared_ptr<Environment> env) : env(env) {
  if (!font.openFromFile("assets/3270-Medium Nerd Font Complete Mono.ttf")) {
    throw std::runtime_error("Failed to load font");
  }
  entitiesCount = initText();
  totalEnergy = initText();
}

// Initialize sf::Text object with default settings
std::unique_ptr<sf::Text> UI::initText() {
  auto text = std::make_unique<sf::Text>(font);
  text->setFont(font);
  text->setCharacterSize(16);
  text->setFillColor(sf::Color::Red);
  text->setStyle(sf::Text::Bold | sf::Text::Underlined);
  return text;
}

// Get custom text with specified position
std::unique_ptr<sf::Text> UI::getText(std::string text, sf::Vector2f p) {
  auto t = initText();
  t->setString(text);
  t->setPosition(p);
  return t;
}
// Draw method to render entity and energy counts
void UI::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  // Update entities count
  entitiesCount->setString("Entities: " + std::to_string(env->entities.size()));
  entitiesCount->setPosition({10, 10});

  // Calculate and update total energy
  totalEnergy->setString(
      "Energy: " +
      std::to_string(std::accumulate(
          env->entities.begin(), env->entities.end(), 0.0f,
          [](float sum, const auto &e) { return sum + e->getEnergy(); })));
  totalEnergy->setPosition({10, 35});

  // Render text to screen
  target.draw(*entitiesCount, states);
  target.draw(*totalEnergy, states);
}
