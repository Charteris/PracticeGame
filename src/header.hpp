#ifndef HEADER
#define HEADER

#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "EntityManager.hpp"
#include "Entities.hpp"
#include "Mesh.hpp"

// Declare functions
void manageEvents(sf::RenderWindow&, Camera&);

#endif