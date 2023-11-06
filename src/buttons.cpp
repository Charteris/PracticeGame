/**
 * Provides functionality for interactive UI elements
 * @author Lachlan Charteris
*/

#include <functional>
#include <iostream>
#include <string>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Buttons.hpp"

/**
 * Constructs a rectangular button with a set position, callback, and graphic
 * @tparam S The type of graphic stored within the Button @def{sf::RectangleShape}
 * @param id The name of the button
 * @param g The graphic for the button
 * @param callback The callback to be called when interacted with
*/
template <typename S>
Button<S>::Button(std::string id, S g, std::function<void()> callback) {
  name = id;
  graphic = g;
  position = g.getPosition();
  scale = g.getScale();
  bounds = sf::FloatRect(position, scale);
  onClickCallback = callback;
}

/**
 * Constructs a rectangular button with a set position, size and callback
 * @param id The name of the button
 * @param pos The position of the button on the render window
 * @param s The size of the button
 * @param callback The callback to be called when interacted with
*/
template <>
Button<sf::RectangleShape>::Button(
  std::string id, sf::Vector2f pos, sf::Vector2f s, std::function<void()> callback
) {
  // Instantiate rectangle object
  sf::RectangleShape g = sf::RectangleShape(sf::Vector2f(1.f, 1.f));
  g.setPosition(pos);
  g.setScale(s);
  g.setFillColor(sf::Color(50, 50, 50));
  g.setOutlineColor(sf::Color(0, 0, 0));
  float scaleMagnitude = std::sqrt(s.x * s.x + s.y * s.y);
  g.setOutlineThickness(5 / scaleMagnitude);

  // Instantiate object from rectangleShape
  name = id;
  graphic = g;
  position = pos;
  scale = s;
  bounds = sf::FloatRect(pos, s);
  onClickCallback = callback;
}

/**
 * Constructs a rectangular button with a set position, callback, and graphic
 * @tparam S The type of graphic stored within the Button @def{sf::RectangleShape}
 * @param id The name of the button
 * @param pos The position of the button on the render window
 * @param g The graphic for the button
 * @param callback The callback to be called when interacted with
*/
template <typename S>
Button<S>::Button(std::string id, sf::Vector2f pos, S g, std::function<void()> callback) {
  Button(id, g, callback);
  position = pos;
  graphic.setPosition(pos);
}

/**
 * Interact with the button
 * @tparam S The type of graphic stored within the Button @def{sf::RectangleShape}
*/
template <typename S>
void Button<S>::interact() {
  if (isMouseInBounds) onClickCallback();
}

/**
 * Renders the button instance
 * @tparam S The type of graphic stored within the Button @def{sf::RectangleShape}
 * @param window The SFML render window to plot on
*/
template <typename S>
void Button<S>::render(sf::RenderWindow &window) {
  window.draw(graphic);
}

template class Button<sf::RectangleShape>;
template class Button<sf::Sprite>;
template class Button<sf::CircleShape>;