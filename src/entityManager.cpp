#include "EntityManager.hpp"

#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <format>

#include <SFML/Graphics.hpp>

#define BUFFER_SIZE 20

/**
 * Constructor from position and drawable
 * @param pos The 2D position vector
 * @param g The drawable object
*/
template <typename S>
GraphicalEntity<S>::GraphicalEntity(std::string id, sf::Vector2f pos, S g) {
  name = id;
  position = pos;
  graphic = g;
  sf::Vector2f tempSize = graphic.getLocalBounds().getSize();
  sf::Vector2f tempScale = graphic.getScale();
  size.x = tempSize.x / tempScale.x;
  size.y = tempSize.y / tempScale.y;
  graphic.setPosition(pos - size / 2.f);
}

/**
 * Constructor from position, size, and drawables
 * @param pos The 2D position vector
 * @param s The 2D size vector
 * @param g The drawable object
*/
template <typename S>
GraphicalEntity<S>::GraphicalEntity(std::string id, sf::Vector2f pos, sf::Vector2f s, S g) {
  sf::Vector2f tempSize = g.getLocalBounds().getSize();
  sf::Vector2f tempScale = g.getScale();
  sf::Vector2f scale(tempSize.x * tempScale.x / s.x, tempSize.y * tempScale.y / s.y);
  g.setScale(scale);
  GraphicalEntity<S>(id, pos, g);
}

/**
 * Checks if the graphical bounds are intersecting with other bounds
 * @param bounds The bounds to check against
*/
template <typename S>
bool GraphicalEntity<S>::intersects(const sf::FloatRect &bounds) { 
  return graphic.getLocalBounds().intersects(bounds); 
};

/**
 * Renders the graphical entity
 * @param window The render window
*/
template <typename S>
void GraphicalEntity<S>::render(sf::RenderWindow &window) { 
  window.draw(graphic); 
};

template class GraphicalEntity<sf::Sprite>;
template class GraphicalEntity<sf::CircleShape>;
template class GraphicalEntity<sf::RectangleShape>;



/**
 * Gets a pointer to the player entity stored in the manager
 * @return A pointer to the player entity
*/
std::shared_ptr<Entity> EntityManager::getPlayer() {
  return entities[playerKey];
};

/**
 * Gets a pointer to an entity from the manager
 * @param id The unique identifier for the entity being retrieved
 * @return A pointer to the entity at the index
*/
std::shared_ptr<Entity> EntityManager::getEntity(std::string id) { 
  return entities[id];
};

/**
 * Find and remove the player entity from the manager
*/
void EntityManager::removePlayer() {
  entities.erase(playerKey);
  playerKey = "";
}

/**
 * Removes and entity from the manager
 * @param index The stored index of the entity to be removed
*/
void EntityManager::removeEntity(std::string id) {
  entities.erase(id); 
};

/**
 * Returns the number of entities within the manager
 * @returns The current number of entities
*/
int EntityManager::size() { 
  return entities.size(); 
};

/**
 * Updates all entities in the manager
*/
void EntityManager::update() { 
  for (auto it = entities.begin(); it != entities.end(); it++) 
    it->second->update(); 
};

/**
 * Renders all entities in the manager
 * @param window The render window
*/
void EntityManager::render(sf::RenderWindow &window) { 
  for (auto it = entities.begin(); it != entities.end(); it++) 
    it->second->render(window); 
  
};

/**
 * Adds entities at positions respective of a position file
 * @param filename The filename of the image being read
 * @param pixelSize The scale factor for instantiated entities @def{32}
 * @param offset The offset origin to begin instantiating objects from @def{(0,0)}
 * @return A list of entities which have been added to the entity manager
 * 
 * TODO: Expand upon this implementation to account for indefinite instances
*/
void EntityManager::addFromFile(const char* filename, float pixelSize, sf::Vector2f offset) {
  sf::Image img;
  img.loadFromFile(filename);
  sf::Vector2u size = img.getSize();
  sf::Vector2f pos;
  std::string name;
  char buffer[BUFFER_SIZE];

  sf::RectangleShape shape(sf::Vector2f(pixelSize, pixelSize));
  shape.setFillColor(sf::Color::Black);
  shape.setOutlineThickness(1);
  shape.setOutlineColor(sf::Color::White);

  // Ensures unique entity names
  // TODO: Adapt this to use a lookup table for color and entity type mappings
  std::unordered_map<std::string, int> entityCount;

  // SFML color constants href=<https://oprypin.github.io/crsfml/api/SF/Color.html>
  sf::Color color;

  // Add entities at positions based on colors
  for (int x = 0; x < size.x; x++) {
    for (int y = 0; y < size.y; y++) {
      color = img.getPixel(x, y);
      if (color == sf::Color::White) continue;

      pos.x = x*pixelSize + offset.x + pixelSize/2;
      pos.y = y*pixelSize + offset.y + pixelSize/2;

      // Creates a wall instance
      if (color == sf::Color::Black) {
        shape.setPosition(pos);
        std::snprintf(buffer, BUFFER_SIZE, "wall_%i\0", ++entityCount["wall"]);
        name.assign(buffer);
        addEntity<GraphicalEntity<sf::RectangleShape>>(name, pos, shape);

      // Creates a player instance
      } else if (color == sf::Color::Blue) {
        sf::CircleShape circleShape(pixelSize / 2);
        circleShape.setFillColor(sf::Color::Blue);
        definePlayer("Player");
        addEntity<GraphicalEntity<sf::CircleShape>>(playerKey, pos, circleShape);
      }
    }
  }
}

/**
 * Destructs all existing entities
*/
EntityManager::~EntityManager() { 
  entities.clear();
};