#ifndef HEADER
#define HEADER

/**
 * Provides a grouped header file containing all relevant templates and functionality
 * @author Lachlan Charteris
*/

#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Include Classes
#include "Resources.hpp"
#include "EntityManager.hpp"
#include "Entities.hpp"
#include "UIElements.hpp"
#include "Projection.hpp"
#include "Mesh.hpp"

// Event Manager Functions
void updateCameraByInput(Camera&, sf::Keyboard::Scancode);
void manageEvents(sf::RenderWindow&, Camera&, EntityManager&);

// Input Validation Functions
std::string validateEquationLogic(std::string);
std::string validateNumeric(std::string);
std::string validateBrackets(std::string);

#endif