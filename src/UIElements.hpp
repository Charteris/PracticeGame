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
class Input : public Entity {
  protected:
    std::function<std::string(std::string)> onBlurCallback = 
      [](std::string input) { return "No callback provided!"; };
    sf::Font font;
    sf::Text displayText, errorText;
    sf::RectangleShape errorBg;
    sf::Texture idle, hovered, active, error;
    sf::Sprite graphic;
    sf::Vertex caret[2];
    sf::Clock clock;
    std::string input = "", errorString = "";
    bool isFocussed = false;
  
  public:
    Input(
      std::string,
      std::function<std::string(std::string)>, 
      sf::Vector2f pos = sf::Vector2f(),
      sf::Vector2f s = sf::Vector2f(128.f, 32.f)
    );
    void instantiateInput(sf::Vector2f, sf::Vector2f);
    void updateCaret();
    void onMouseHover();
    void onBlur();
    void interact(sf::Mouse::Button, bool isMouseReleased = false);
    void applyKeyInput(int);
    void render(sf::RenderWindow&);
    void troubleshoot();
};

#endif