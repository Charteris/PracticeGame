#ifndef BUTTONS
#define BUTTONS

/**
 * Provides template definitions for UI elements
 * @author Lachlan Charteris
*/

#include <functional>
#include <iostream>
#include <type_traits>

#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"

/**
 * A simple button class for the UI
 * @tparam S The type of graphic stored within the Button @def{sf::RectangleShape}
*/
template <typename S = sf::RectangleShape>
class Button : public Entity {
  protected:
    std::function<void()> onClickCallback = []() { 
      std::cout << "No callback provided!" << std::endl; 
    };
    S graphic;
  
  public:
    Button(std::string, S, std::function<void()>);
    Button(std::string, sf::Vector2f, sf::Vector2f, std::function<void()>);
    Button(std::string, sf::Vector2f, S, std::function<void()>);
    
    template <typename U = S>
    std::enable_if_t<sizeof(U) && (std::is_same<U, sf::Sprite>::value == false)>
    onMouseHover() {
      std::cout << "Mouse Hovered" << std::endl;
      graphic.setOutlineColor(isMouseInBounds ? sf::Color(100, 100, 100) : sf::Color(0, 0, 0));
    };

    void interact();
    void render(sf::RenderWindow&);
    void troubleshoot() {
      sf::Vector2f pos = graphic.getPosition();
      sf::Vector2f s = graphic.getScale();
      std::cout << pos.x << " " << pos.y << " " << s.x << " " << s.y << " " << 
        position.x << " " << position.y << " " << scale.x << " " << scale.y << std::endl;
    };
};

#endif