#include "../include/Config.h"
#include "../include/Environement/Entity.h"
#include "../include/Environement/Environment.h"
#include "../include/Rendering/Rendering.h"
#include "../include/Rendering/UI.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
  sf::RenderWindow window(sf::VideoMode(Config::WIDTH, Config::HEIGHT),
                          Config::TITLE, sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true); // sync with graphics card refresh rate
  window.setPosition(sf::Vector2i(100, 400));

  // std::shared_ptr<Environment> environment = std::make_shared<Environment>();
  std::shared_ptr<Environment> environment =
    std::make_shared<Environment>(1000);
  DrawableEntities drawableElements(environment->entities);
  DrawablePhysics drawablePhysics(environment->physics);
  UI ui(environment);
  // sf::View view(sf::FloatRect(0, 0, Config::WIDTH, Config::HEIGHT));
  // view.zoom(2);
  // window.setView(view);
  // run the main loop

  sf::Clock clock;
  float lastTime = 0;
  float fps = 0;
  while (window.isOpen()) {
    clock.restart();
    // handle events
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    environment->update(0.01);

    // draw it
    window.clear();
    window.draw(drawableElements);
    if (Config::drawPhysics) {
      window.draw(drawablePhysics);
    }
    window.draw(ui);
    window.draw(ui.getText("FPS: " + std::to_string(int(fps)),
                           sf::Vector2f(Config::WIDTH - 200, 10)));
    window.display();
    fps = 1.f / clock.getElapsedTime().asSeconds();
  }

  return 0;
}
