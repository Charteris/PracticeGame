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

// Include classes
#include "EntityManager.hpp"
#include "Entities.hpp"
#include "Buttons.hpp"
#include "Projection.hpp"
#include "Mesh.hpp"

// Declare functions
void updateCameraByInput(Camera&, sf::Keyboard::Scancode);
void manageEvents(sf::RenderWindow&, Camera&, EntityManager&);

#endif