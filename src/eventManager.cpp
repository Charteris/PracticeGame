#include "Header.hpp"

void manageEvents(sf::RenderWindow &window) {
  sf::Event event;
  int width, height;
  while (window.pollEvent(event))
  {
    switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        if (event.key.scancode == sf::Keyboard::Scan::Escape)
          window.close();
        break;

      case sf::Event::Resized:
        width = event.size.width;
        height = event.size.height;
        std::cout << "New Window Size: (" << width << ", " << height << ")" << std::endl;
        break;

      case sf::Event::LostFocus:
        std::cout << "Lost Focus" << std::endl;
        break;

      case sf::Event::GainedFocus:
        std::cout << "Gained Focus" << std::endl;
        break;

      case sf::Event::MouseEntered:
        std::cout << "Mouse Entered The Screen" << std::endl;
        break;

      case sf::Event::MouseLeft:
        std::cout << "Mouse Left The Screen" << std::endl;
        break;

      case sf::Event::TextEntered:
        if (event.text.unicode < 128)
          std::cout << static_cast<char>(event.text.unicode);
        break;

      case sf::Event::MouseWheelScrolled:
        std::cout << "New Mouse Position: (" << event.mouseWheelScroll.x << ", " << event.mouseWheelScroll.y << ")" << std::endl;
        break;

      case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Right)
          std::cout << "Mouse Pressed At: (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
        break;

      case sf::Event::MouseMoved:
        break;

      case sf::Event::JoystickMoved:
        if (event.joystickMove.axis == sf::Joystick::X)
          std::cout << "Joystick " << event.joystickMove.joystickId << " moved to " << event.joystickMove.position << std::endl;
        break;

      case sf::Event::JoystickConnected:
        std::cout << "Joystick " << event.joystickConnect.joystickId << " connected" << std::endl;
        break;

      case sf::Event::JoystickDisconnected:
        std::cout << "Joystick " << event.joystickConnect.joystickId << " disconnected" << std::endl;
        break;

      default:
        break;
    }
  }
}