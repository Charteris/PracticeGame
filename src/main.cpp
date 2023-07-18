#include "Header.hpp"

int main()
{
  // Simple circle rendering
  int width = 1280, height = 960;
  sf::RenderWindow window(sf::VideoMode(width, height), "SFML App");
  sf::Color bgColor = sf::Color(150, 150, 150);
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  // Create texture
  sf::Texture texture;
  texture.loadFromFile("res/Tile.png");
  texture.setRepeated(true);
  sf::Sprite sprite(texture);
  sprite.setPosition(sf::Vector2f(width / 2, height / 2));

  // Create text
  int textSize = 32;
  sf::Vector2i pos = sf::Mouse::getPosition();
  char buffer[100];
  std::sprintf(buffer, "Mouse Position: (%.3f, %.3f)", pos.x, pos.y);

  sf::Font font;
  font.loadFromFile("res/arial.ttf");

  sf::Text text;
  text.setFont(font);
  text.setFillColor(sf::Color::Red);
  text.setString(buffer);
  text.setCharacterSize(textSize);
  text.setStyle(sf::Text::Bold);
  text.setPosition(sf::Vector2f(width / 2, height / 2));

  // Render 3D mesh
  Mesh newMesh("res/Person_model.obj");

  // Define Entity Manager
  EntityManager entityManager;
  long long int counter = 1;
  entityManager.addFromFile("res/simpleScene.png");
  std::cout << "Length: " << entityManager.size() << std::endl;

  int frames = 0;
  sf::Clock clock;
  clock.restart();
  while (window.isOpen())
  {
    // Support events
    manageEvents(window);

    // Clear screen, render items, and display new buffer
    window.clear(bgColor);
    entityManager.render(window);
    window.display();

    // Continuous troubleshooting
    ++frames;
    if (clock.getElapsedTime().asSeconds() >= 1) { 
      std::cout << "FPS: " << frames << std::endl;
      std::cout << "Mouse position: " << pos.x << ", " << pos.y << std::endl;
      clock.restart();
      frames = 0;
    }
  }

  return 0;
}