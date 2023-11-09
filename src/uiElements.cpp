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
#include "Resources.hpp"

#define BACKSPACE 8
#define ENTER 13

/**
 * Constructs a rectangular button with a set position, size and callback
 * @param id The name of the button
 * @param title The title to be displayed on the button
 * @param callback The callback to be called when interacted with
 * @param pos The position of the button on the render window @def{sf::Vector2f(0, 0)}
 * @param s The size of the button @def{sf::Vector2f(128, 64)}
*/
Button::Button(
  std::string id,
  std::string title, 
  std::function<void()> callback,
  sf::Vector2f pos, 
  sf::Vector2f s
) {
  instantiateButton(title, pos, s);
  sf::Vector2u textureSize = resources::TextureMap["BUTTON"].getSize();
  sf::Sprite sprite(resources::TextureMap["BUTTON"]);
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
  displayText.setFont(resources::ArialFont);
  displayText.setFillColor(resources::ColorMap["TEXT"]);
  displayText.setString(title);
  displayText.setCharacterSize(resources::TextSize);
  displayText.setStyle(sf::Text::Bold);
  sf::Vector2f offset = origin + s / 2.f - sf::Vector2f(
      resources::TextSize / 4.f * title.length(), resources::TextSize / 2.f
    );
  displayText.setPosition(offset);
}

/**
 * Provides a callback function to be called when the mouse hovers over the button
*/
void Button::onMouseHover() {
  graphic.setTexture(
    isMouseInBounds 
      ? resources::TextureMap["BUTTON_HOVERED"] 
      : resources::TextureMap["BUTTON"]
  );
};

/**
 * Interact with the button
 * @param mouseEvent The mouse event invoking the function call
 * @param isMouseReleased Whether the mouse event has been released @def{false}
*/
void Button::interact(sf::Mouse::Button mouseEvent, bool isMouseReleased) {
  if (mouseEvent == sf::Mouse::Left) {
    if (isMouseReleased) {
      graphic.setTexture(resources::TextureMap["BUTTON"]);
      if (isMouseInBounds) onClickCallback();
    } else if (isMouseInBounds) {
      graphic.setTexture(resources::TextureMap["BUTTON_PRESSED"]);
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
  std::function<std::string(std::string)> callback, 
  sf::Vector2f pos, 
  sf::Vector2f s
) {
  instantiateInput(pos, s);

  sf::Vector2u textureSize = resources::TextureMap["INPUT"].getSize();
  sf::Sprite sprite(resources::TextureMap["INPUT"]);
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
  displayText.setFont(resources::ArialFont);
  displayText.setFillColor(resources::ColorMap["TEXT"]);
  displayText.setString(input);
  displayText.setCharacterSize(resources::TextSize);
  displayText.setStyle(sf::Text::Bold);
  sf::Vector2f offset = origin 
    + sf::Vector2f(0.1f * s.x, s.y / 2.f - resources::TextSize / 2.f);
  displayText.setPosition(offset);
  
  // Instantiate error string text
  errorBg = sf::RectangleShape();
  errorText.setFont(resources::ArialFont);
  errorText.setFillColor(resources::ColorMap["TOOLTIP"]);
  errorText.setString(errorString);
  errorText.setCharacterSize(resources::TooltipSize);
  errorText.setStyle(sf::Text::Italic);

  // Instantiate Caret (input cursor)
  caret[0].position = origin + sf::Vector2f(0.1f * s.x, 0.2f * s.y);
  caret[0].color = resources::ColorMap["VERTICES"];
  caret[1].position = origin + sf::Vector2f(0.1f * s.x, 0.8f * s.y);
  caret[1].color = resources::ColorMap["VERTICES"];
}

/**
 * Updates the position of the Caret cursor
*/
void Input::updateCaretPos() {
  float textWidth = displayText.getLocalBounds().width;
  caret[0].position = position + sf::Vector2f(0.1f * scale.x + textWidth, 0.2f * scale.y);
  caret[1].position = position + sf::Vector2f(0.1f * scale.x + textWidth, 0.8f * scale.y);
}

/**
 * Provides a callback function to be called when the mouse hovers over the button
*/
void Input::onMouseHover() {
  if (isFocussed) graphic.setTexture(resources::TextureMap["INPUT_ACTIVE"]);
  else if (isMouseInBounds) graphic.setTexture(resources::TextureMap["INPUT_HOVERED"]);
  else graphic.setTexture(
    errorString.empty() 
      ? resources::TextureMap["INPUT"] 
      : resources::TextureMap["INPUT_ERROR"]
  );
};

/**
 * A helper function to be called whenever the blur event is invoked
*/
void Input::onBlur() {
  errorString = onBlurCallback(input);
  if (errorString.empty()) {
    displayText.setFillColor(resources::ColorMap["TEXT"]);
    
  } else {
    displayText.setFillColor(resources::ColorMap["ERROR"]);
    errorText.setString(errorString);
    errorBg.setSize(errorText.getLocalBounds().getSize() + sf::Vector2f(2.f, 2.f));
  }
}

/**
 * Focus or unfocus the input field
 * @param mouseEvent The mouse event invoking the function call
 * @param isMouseReleased Whether the mouse event has been released @def{false}
*/
void Input::interact(sf::Mouse::Button mouseEvent, bool isMouseReleased) {
  if (mouseEvent == sf::Mouse::Left) {
    if (isFocussed && !isMouseInBounds) onBlur();
    if (!isFocussed && isMouseInBounds) {
      displayText.setFillColor(resources::ColorMap["TEXT"]);
      caretIndex = input.length() - 1;
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
    onBlur();
    onMouseHover();
  } else if (inputKey == BACKSPACE) {
    if (!input.empty()) {
      input.pop_back();
      caretIndex --;
    }
  } else if (inputKey < 128) {
    char key = static_cast<char>(inputKey);
    input += key;
    caretIndex ++;
  } else return;
  displayText.setString(input);
  updateCaretPos();
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

  // Display error tooltip when hovered and erroneous
  if (!errorString.empty() && isMouseInBounds) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    errorText.setPosition(mousePos.x + 1, mousePos.y + 1 - 12);
    errorBg.setPosition(mousePos.x, mousePos.y - 10);
    window.draw(errorBg);
    window.draw(errorText);
  }
}

/**
 * Displays troubleshooting information through the console
*/
void Input::troubleshoot() {
  std::cout << name << ": " << position.x << " " << position.y << " | "
    << scale.x << " " << scale.y << std::endl;
}