/**
 * The main execution script for the Radar Simulator project
 * @author Lachlan Charteris
*/

#include <memory>
#include <math.h>

#include "Header.hpp"
#include "Buttons.hpp"

#define _USE_MATH_DEFINES

int main()
{
  // Simple circle rendering
  const int WIDTH = 1280, HEIGHT = 960;
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML App");
  sf::Color bgColor = sf::Color(sf::Color::White);
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  // Create texture
  sf::Texture texture;
  texture.loadFromFile("res/Tile.png");
  texture.setRepeated(true);
  sf::Sprite sprite(texture);
  sprite.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));

  // Create text
  int textSize = 14;
  sf::Vector2i pos = sf::Mouse::getPosition();
  char buffer[100];
  std::sprintf(buffer, "Mouse Position: (%.3f, %.3f)", pos.x, pos.y);

  sf::Font font;
  font.loadFromFile("res/arial.ttf");

  sf::Text text;
  text.setFont(font);
  text.setFillColor(sf::Color::Black);
  text.setString(buffer);
  text.setCharacterSize(textSize);
  text.setStyle(sf::Text::Bold);
  text.setPosition(sf::Vector2f(WIDTH / 2, HEIGHT / 2));

  // Define 3D camera
  Camera camera;
  sf::Vector3f cameraPos = camera.getPosition(), cameraRot = camera.getOrientation();

  sf::Text positionText(text);
  std::sprintf(
    buffer, "Camera Position: (%.3f, %.3f, %.3f)", cameraPos.x, cameraPos.y, cameraPos.z
  );
  positionText.setString(buffer);
  positionText.setPosition(sf::Vector2f(2, 2));

  sf::Text angleText(text);
  std::sprintf(
    buffer, "Camera Angle: (%.3f, %.3f, %.3f)", cameraRot.x, cameraRot.y, cameraRot.z
  );
  angleText.setString(buffer);
  angleText.setPosition(sf::Vector2f(2, 2 + textSize*1.2));

  // Define Entity Manager
  EntityManager entityManager;
  long long int counter = 1;
  float step = M_PI / 4280;
  std::shared_ptr<MeshEntity> entity = entityManager.addEntity<MeshEntity>(
    "mesh", sf::Vector3f(WIDTH / 2, HEIGHT / 2, 1.f), &camera, "res/Person_model.obj"
  );

  // Add UI Entities
  std::shared_ptr<Button<sf::RectangleShape>> button = 
    entityManager.addUIElement<Button<sf::RectangleShape>>(
      "button", sf::Vector2f(WIDTH - 100, HEIGHT / 8), sf::Vector2f(100, 100), []() { 
        std::cout << "Button Callback" << std::endl;
      }
    );

  // entityManager.addFromFile("res/simpleScene.png");
  // std::cout << "Length: " << entityManager.size() << std::endl;

  int frames = 0;
  sf::Clock clock;
  clock.restart();
  while (window.isOpen())
  {
    // Support events
    manageEvents(window, camera, entityManager);

    // Clear screen, render items, and display new buffer
    window.clear(bgColor);
    
    // entity->rotate(sf::Vector3f(0, step, 0));
    entityManager.render(window);

    // Display camera details
    std::sprintf(
      buffer, "Camera Position: (%.3f, %.3f, %.3f)", cameraPos.x, cameraPos.y, cameraPos.z
    );
    positionText.setString(buffer);
    window.draw(positionText);

    std::sprintf(
      buffer, "Camera Angle: (%.3f, %.3f, %.3f)", cameraRot.x, cameraRot.y, cameraRot.z
    );
    angleText.setString(buffer);
    window.draw(angleText);

    window.display();

    // Continuous troubleshooting
    ++frames;
    // if (clock.getElapsedTime().asSeconds() >= 1) { 
    //   std::cout << "FPS: " << frames << std::endl;
    //   clock.restart();
    //   frames = 0;
    //   button->troubleshoot();
    // }
  }

  return 0;
}