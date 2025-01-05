#include <SFML/Graphics.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "Config.h"
#include "model/Entity/Entity.h"
#include "model/Environment/Environment.h"
#include "view/Rendering/DrawablePhysics.h"
#include "view/Rendering/Rendering.h"
#include "view/Rendering/UI.h"

int main() {
  sf::RenderWindow window(sf::VideoMode({Config::WIDTH, Config::HEIGHT}),
                          Config::TITLE, sf::Style::Titlebar);
  window.setVerticalSyncEnabled(true); // sync with graphics card refresh rate
  window.setPosition(sf::Vector2i(100, 400));

  // std::shared_ptr<Environment> environment = std::make_shared<Environment>();
  std::shared_ptr<Environment> environment = std::make_shared<Environment>(100);
  DrawableEntities drawableElements(environment->entities);
  DrawablePhysics drawablePhysics(environment->physics);
  UI ui(environment);
  // sf::View view(sf::FloatRect(0, 0, Config::WIDTH, Config::HEIGHT));
  // view.zoom(2);
  // window.setView(view);
  // run the main loop

  sf::Clock clock;
  float lastTime = 0;
  float currentFps = 0;
  std::string fpsToDraw = std::to_string(currentFps);
  float fpsRenderPeriod = 0;

  while (window.isOpen()) {
    clock.restart();
    // handle events
    // handle events
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    environment->update(0.01);

    // draw it
    window.clear();
    window.draw(drawableElements);
    if (Config::drawPhysics) {
      window.draw(drawablePhysics);
    }
    window.draw(ui);
    if (fpsRenderPeriod > 1) {
      std::ostringstream oss;
      oss << std::fixed << std::setprecision(1) << currentFps;
      fpsToDraw = oss.str(); // "60.1"

      fpsRenderPeriod = 0;
    }
    window.draw(
        ui.getText("FPS: " + fpsToDraw, sf::Vector2f(Config::WIDTH - 200, 10)));
    window.display();
    currentFps = 1.f / clock.getElapsedTime().asSeconds();
    fpsRenderPeriod += clock.getElapsedTime().asSeconds();
  }

  return 0;
}
