/**
 * Provides functionality for handling input events
 * @author Lachlan Charteris
*/

#include <math.h>

#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"
#include "Projection.hpp"
#include "Mesh.hpp"

#define _USE_MATH_DEFINES

/**
 * Updates the camera position or rotation by the user input
 * @param camera The camera instance to be updated
 * @param keycode The keycode scanned from the input keyboard press
*/
void updateCameraByInput(Camera &camera, sf::Keyboard::Scancode keycode) {
  float rotationFactor = M_PI / 180.0f;
  if (keycode == sf::Keyboard::Scan::W) { // Move camera
    camera.moveCamera(sf::Vector3f(0, 0, 0.1));
  } else if (keycode == sf::Keyboard::Scan::S) {
    camera.moveCamera(sf::Vector3f(0, 0, -0.1));
  } else if (keycode == sf::Keyboard::Scan::D) {
    camera.moveCamera(sf::Vector3f(2, 0, 0));
  } else if (keycode == sf::Keyboard::Scan::A) {
    camera.moveCamera(sf::Vector3f(-2, 0, 0));
  } else if (keycode == sf::Keyboard::Scan::LShift) {
    camera.moveCamera(sf::Vector3f(0, -2, 0));
  } else if (keycode == sf::Keyboard::Scan::Space) {
    camera.moveCamera(sf::Vector3f(0, 2, 0));

  } else if (keycode == sf::Keyboard::Scan::Q) { // Rotate camera
    camera.rotateCamera(sf::Vector3f(0, -rotationFactor, 0));
  } else if (keycode == sf::Keyboard::Scan::E) {
    camera.rotateCamera(sf::Vector3f(0, rotationFactor, 0));
  } else if (keycode == sf::Keyboard::Scan::Z) {
    camera.rotateCamera(sf::Vector3f(0, 0, -rotationFactor));
  } else if (keycode == sf::Keyboard::Scan::C) {
    camera.rotateCamera(sf::Vector3f(0, 0, rotationFactor));
  } else if (keycode == sf::Keyboard::Scan::F) {
    camera.rotateCamera(sf::Vector3f(-rotationFactor, 0, 0));
  } else if (keycode == sf::Keyboard::Scan::R) {
    camera.rotateCamera(sf::Vector3f(rotationFactor, 0, 0));
  }
}

/**
 * Handles user input events for the camera and entity manager
 * @param window The SFML render window to plot on
 * @param camera The camera instance to control
 * @param manager The entity manager to control UI and entity components
*/
void manageEvents(sf::RenderWindow &window, Camera &camera, EntityManager &manager) {
  sf::Event event;
  int width, height;
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        if (event.key.scancode == sf::Keyboard::Scan::Escape) // Exit
          window.close();
        updateCameraByInput(camera, event.key.scancode);
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
        manager.applyKeyInput(event.text.unicode);
        break;

      case sf::Event::MouseWheelScrolled:
        std::cout << "New Mouse Position: (" << event.mouseWheelScroll.x << ", " << event.mouseWheelScroll.y << ")" << std::endl;
        break;

      case sf::Event::MouseButtonPressed:
        manager.interact(event.mouseButton.button);
        break;

      case sf::Event::MouseButtonReleased:
        manager.interact(event.mouseButton.button, true);
        break;

      case sf::Event::MouseMoved:
        manager.checkMousePosition(sf::Mouse::getPosition(window));
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