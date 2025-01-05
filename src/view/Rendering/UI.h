#ifndef UI_HEADER
#define UI_HEADER

#include <SFML/Graphics.hpp>
#include <memory>
#include <model/Entity/Entity.h>

class UI : public sf::Drawable {
public:
  explicit UI(std::shared_ptr<Environment> env);
  std::unique_ptr<sf::Text> getText(std::string text, sf::Vector2f p);

protected:
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;

private:
  std::unique_ptr<sf::Text> initText();
  std::shared_ptr<Environment> env;
  sf::Font font;
  std::unique_ptr<sf::Text> entitiesCount;
  std::unique_ptr<sf::Text> totalEnergy;
};

#endif // UI_HEADER
