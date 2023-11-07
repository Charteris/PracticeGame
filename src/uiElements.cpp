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

#define BACKSPACE 8
#define ENTER 13

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
  int textSize = 14;
  font.loadFromFile("res/arial.ttf");
  displayText.setFont(font);
  displayText.setFillColor(sf::Color(240, 240, 240));
  displayText.setString(title);
  displayText.setCharacterSize(textSize);
  displayText.setStyle(sf::Text::Bold);
  sf::Vector2f offset = origin + s / 2.f 
    - sf::Vector2f(textSize / 4.f * title.length(), textSize / 2.f);
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
    if (isMouseReleased) {
      graphic.setTexture(idle);
      if (isMouseInBounds) onClickCallback();
    } else if (isMouseInBounds) {
      graphic.setTexture(pressed);
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



/**
 * Constructs a rectangular button with a set position, size and callback
 * @param id The name of the button
 * @param callback The callback to be called when the input field is blurred, expecting a
 *          a boolean value returned to indicate whether the input field is erroneous
 * @param pos The position of the button on the render window @def{sf::Vector2f(0, 0)}
 * @param s The size of the button @def{sf::Vector2f(128, 48)}
*/
Input::Input(
  std::string id, 
  std::function<bool(std::string)> callback, 
  sf::Vector2f pos, 
  sf::Vector2f s
) {
  instantiateInput(pos, s);
  idle.loadFromFile("res/Input.png");
  hovered.loadFromFile("res/InputHovered.png");
  active.loadFromFile("res/InputActive.png");
  error.loadFromFile("res/InputError.png");

  sf::Vector2u textureSize = idle.getSize();
  sf::Sprite sprite(idle);
  sprite.setPosition(pos);
  sprite.setScale(sf::Vector2f(s.x / textureSize.x, s.y / textureSize.y));

  // Instantiate object from rectangleShape
  name = id;
  graphic = sprite;
  position = pos;
  scale = s;
  bounds = sf::FloatRect(pos, s);
  onBlurCallback = callback;
}

/**
 * Instantiates the SFML text object to display the button title
 * @param origin The origin of the text to be displayed
 * @param s The size of the button
*/
void Input::instantiateInput(sf::Vector2f origin, sf::Vector2f s) {
  int textSize = 14;
  font.loadFromFile("res/arial.ttf");
  displayText.setFont(font);
  displayText.setFillColor(sf::Color(240, 240, 240));
  displayText.setString(input);
  displayText.setCharacterSize(textSize);
  displayText.setStyle(sf::Text::Bold);
  sf::Vector2f offset = origin 
    + sf::Vector2f(0.1f * s.x, s.y / 2.f - textSize / 2.f);
  displayText.setPosition(offset);

  // Instantiate Caret (input cursor)
  caret[0].position = origin + sf::Vector2f(0.1f * s.x, 0.2f * s.y);
  caret[0].color = sf::Color(200, 200, 200);
  caret[1].position = origin + sf::Vector2f(0.1f * s.x, 0.8f * s.y);
  caret[1].color = sf::Color(200, 200, 200);
}

void Input::updateCaret() {
  float textWidth = displayText.getLocalBounds().width;
  caret[0].position = position + sf::Vector2f(0.1f * scale.x + textWidth, 0.2f * scale.y);
  caret[1].position = position + sf::Vector2f(0.1f * scale.x + textWidth, 0.8f * scale.y);
}

/**
 * Provides a callback function to be called when the mouse hovers over the button
*/
void Input::onMouseHover() {
  if (isFocussed) graphic.setTexture(active);
  else if (isMouseInBounds) graphic.setTexture(hovered);
  else graphic.setTexture(isErroneous ? error : idle);
};

/**
 * Focus or unfocus the input field
 * @param mouseEvent The mouse event invoking the function call
 * @param isMouseReleased Whether the mouse event has been released @def{false}
*/
void Input::interact(sf::Mouse::Button mouseEvent, bool isMouseReleased) {
  if (mouseEvent == sf::Mouse::Left) {
    if (isFocussed && !isMouseInBounds) { // Blur event
      isErroneous = onBlurCallback(input);
      displayText.setFillColor(
        isErroneous ? sf::Color(100, 0, 0) : sf::Color(240, 240, 240)
      );
    }
    isFocussed = isMouseInBounds;
    onMouseHover();
  } 
}

/**
 * Allow the user to input a character to the input field
 * @param inputKey The integer unicode value for the input character
*/
void Input::applyKeyInput(int inputKey) {
  if (inputKey == ENTER) {
    // Unfocus from input field
    isFocussed = false;
    isErroneous = onBlurCallback(input);
    displayText.setFillColor(isErroneous ? sf::Color(100, 0, 0) : sf::Color(240, 240, 240));
    onMouseHover();

  } else if (inputKey == BACKSPACE) {
    input.pop_back();

  } else if (inputKey < 128) {
    char key = static_cast<char>(inputKey);
    input += key;

  } else return;
  displayText.setString(input);
  updateCaret();
}

/**
 * Renders the button instance
 * @param window The SFML render window to plot on
*/
void Input::render(sf::RenderWindow &window) {
  window.draw(graphic);
  window.draw(displayText);
  // Display Caret when active
  if (isFocussed) {
    double elapsedTime = clock.getElapsedTime().asSeconds();
    if (elapsedTime >= 0.4) window.draw(caret, 2, sf::Lines);
    if (elapsedTime >= 0.8) clock.restart();
  }
}

/**
 * Displays troubleshooting information through the console
*/
void Input::troubleshoot() {
  std::cout << name << ": " << position.x << " " << position.y << " | "
    << scale.x << " " << scale.y << std::endl;
}