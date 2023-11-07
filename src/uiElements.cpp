/**
 * Provides functionality for interactive UI elements
 * @author Lachlan Charteris
*/

#include <functional>
#include <iostream>
#include <string>
#include <cmath>
#include <typeinfo>

#include <SFML/Graphics.hpp>

#include "UIElements.hpp"

/**
 * Constructs a rectangular button with a set position, size and callback
 * @param id The name of the button
 * @param title The title to be displayed on the button
 * @param callback The callback to be called when interacted with
 * @param pos The position of the button on the render window @def{sf::Vector2f(0, 0)}
 * @param s The size of the button @def{sf::Vector2f(128, 64)}
 * @param idleTextureName The name of the idle button texture @def{res/Button.png}
 * @param hoveredTextureName 
 *          The name of the hovered button texture @def{res/ButtonHovered.png}
 * @param pressedTextureName 
 *          The name of the pressed button texture @def{res/ButtonPressed.png}
*/
Button::Button(
  std::string id,
  std::string title, 
  std::function<void()> callback,
  sf::Vector2f pos, 
  sf::Vector2f s, 
  std::string idleTextureName,
  std::string hoveredTextureName,
  std::string pressedTextureName
) {
  instantiateButton(title, pos, s);
  idle.loadFromFile(idleTextureName);
  hovered.loadFromFile(hoveredTextureName);
  pressed.loadFromFile(pressedTextureName);

  sf::Vector2u textureSize = idle.getSize();
  sf::Sprite sprite(idle);
  sprite.setPosition(pos);
  sprite.setScale(sf::Vector2f(s.x / textureSize.x, s.y / textureSize.y));

  sf::Vector2f size = sprite.getScale();
  std::cout << size.x << " " << size.y << std::endl;

  // Instantiate object from rectangleShape
  name = id;
  graphic = sprite;
  position = pos;
  scale = s;
  bounds = sf::FloatRect(pos, s);
  onClickCallback = callback;
}

/**
 * Instantiates the SFML text object to display the button title
 * @param title The title string to be displayed through the text
 * @param origin The origin of the text to be displayed
 * @param s The size of the button
*/
void Button::instantiateButton(std::string title, sf::Vector2f origin, sf::Vector2f s) {
  int textSize = 12;
  font.loadFromFile("res/arial.ttf");
  displayText.setFont(font);
  displayText.setFillColor(sf::Color::Black);
  displayText.setString(title);
  displayText.setCharacterSize(textSize);
  displayText.setStyle(sf::Text::Bold);
  sf::Vector2f offset = origin + s / 2.f - sf::Vector2f(textSize / 4.f * title.length(), textSize / 2.f);
  displayText.setPosition(offset);
}

/**
 * Provides a callback function to be called when the mouse hovers over the button
*/
void Button::onMouseHover() {
  graphic.setTexture(isMouseInBounds ? hovered : idle);
};

/**
 * Interact with the button
 * @param mouseEvent The mouse event invoking the function call
 * @param isMouseReleased Whether the mouse event has been released @def{false}
*/
void Button::interact(sf::Mouse::Button mouseEvent, bool isMouseReleased) {
  if (mouseEvent == sf::Mouse::Left) {
    if (!isMouseReleased) graphic.setTexture(pressed);
    if (isMouseReleased && isMouseInBounds) {
      graphic.setTexture(idle);
      onClickCallback();
    }
  } 
}

/**
 * Renders the button instance
 * @param window The SFML render window to plot on
*/
void Button::render(sf::RenderWindow &window) {
  window.draw(graphic);
  window.draw(displayText);
}

/**
 * Displays troubleshooting information through the console
*/
void Button::troubleshoot() {
  std::cout << name << ": " << position.x << " " << position.y << " | "
    << scale.x << " " << scale.y << std::endl;
}



