#ifndef UI_Elements
#define UI_Elements

/**
 * Provides template definitions for UI elements
 * @author Lachlan Charteris
*/

#include <functional>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"

/**
 * A simple button class for the UI
*/
class Button : public Entity {
  protected:
    std::function<void()> onClickCallback = []() { 
      std::cout << "No callback provided!" << std::endl; 
    };
    sf::Font font;
    sf::Text displayText;
    sf::Texture idle, hovered, pressed;
    sf::Sprite graphic;
  
  public:
    Button(
      std::string, 
      std::string, 
      std::function<void()>, 
      sf::Vector2f pos = sf::Vector2f(),
      sf::Vector2f s = sf::Vector2f(128.f, 64.f), 
      std::string idleTextureName = "res/Button.png",
      std::string hoveredTextureName = "res/ButtonHovered.png",
      std::string pressedTextureName = "res/ButtonPressed.png"
    );
    void instantiateButton(std::string, sf::Vector2f, sf::Vector2f);
    void onMouseHover();
    void interact(sf::Mouse::Button, bool isMouseReleased = false);
    void render(sf::RenderWindow&);
    void troubleshoot();
};

/**
 * A simple input class for the UI
*/
// class Input : public Entity {
//   protected:
//     std::function<std::string(std::string)> onBlurCallback = []() { 
//       std::cout << "No callback provided!" << std::endl; 
//     };
//     sf::Font font;
//     sf::Text displayText;
//     sf::Texture idle, active;
//     sf::Sprite graphic;
  
//   public:
//     Button(
//       std::string, 
//       std::string, 
//       std::function<void()>, 
//       sf::Vector2f pos = sf::Vector2f(),
//       sf::Vector2f s = sf::Vector2f(128.f, 64.f), 
//       std::string idleTextureName = "res/Button.png",
//       std::string hoveredTextureName = "res/ButtonHovered.png",
//       std::string pressedTextureName = "res/ButtonPressed.png"
//     );
//     void instantiateInput(std::string, sf::Vector2f, sf::Vector2f);
//     void onMouseHover();
//     void interact(sf::Mouse::Button, bool isMouseReleased = false);
//     void render(sf::RenderWindow&);
//     void troubleshoot();
// };

#endif