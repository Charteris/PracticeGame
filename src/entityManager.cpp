/**
 * Provides functionality for default entities and the entity manager
 * @author Lachlan Charteris
*/

#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <format>

#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"
#include "Entities.hpp"

#define BUFFER_SIZE 20

/**
 * Default empty constructor for entity object
*/
Entity::Entity() { };

/**
 * Entity constructor with defined name
 * @param id The name of the new entity
 * @overload
*/
Entity::Entity(std::string id) : name(id) { };

/**
 * Entity constructor with defined name and position
 * @param id The name of the new entity
 * @param pos The 2D position of the entity
 * @overload
*/
Entity::Entity(std::string id, sf::Vector2f pos) 
  : name(id), position(pos), bounds(sf::FloatRect(pos.x + 0.5, pos.y + 0.5, 1, 1)) { };

/**
 * Entity constructor with defined name, position, and scale
 * @param id The name of the new entity
 * @param pos The 2D position of the entity
 * @param s The 2D scale of the new entity
 * @overload
*/
Entity::Entity(std::string id, sf::Vector2f pos, sf::Vector2f s) 
  : name(id), position(pos), bounds(sf::FloatRect(pos + s / 2.f, s)) { };

/**
 * Checks if the mouse has moved in bounds - invoked externally by eventManager
 * @param mousePos The new position of the mouse on the screen
*/
void Entity::checkMousePosition(sf::Vector2i mousePos) {
  bool mouseInBounds = contains(mousePos);
  if (mouseInBounds != isMouseInBounds) {
    std::cout << "Updating mouse hover" << std::endl;
    isMouseInBounds = mouseInBounds;
    onMouseHover();
  }
}

/**
 * Checks if another entity intersects with the current entities bounds
 * @param entity The other entity to check against
 * @return True if the other entity intersects with the current entities bounds
*/
bool Entity::intersects(Entity &entity) { 
  return bounds.intersects(entity.getBounds()); 
};

/**
 * Checks if a set of bounds intersects with the current entities bounds
 * @param rect The rectangular bounds to check against
 * @return True if the rectangular bounds intersects with the current entities bounds
 * @overload
*/
bool Entity::intersects(sf::FloatRect rect) { 
  return bounds.intersects(rect); 
};

/**
 * Checks if a vector point is contained within the current entities bounds
 * @param point The floating x and y position to check against
 * @return True if the point is contained within the current entities bounds
*/
bool Entity::contains(sf::Vector2f point) { 
  return bounds.contains(point); 
};

/**
 * Checks if a vector point is contained within the current entities bounds
 * @param point The integer x and y position to check against
 * @return True if the point is contained within the current entities bounds
 * @overload
*/
bool Entity::contains(sf::Vector2i point) { 
  return bounds.contains(point.x, point.y); 
};

/**
 * Returns a copy of the current entities floating-point bounding rectangle
 * @return A floating-point rectangle proportional to the current entities bounds
*/
sf::FloatRect Entity::getBounds() { 
  return bounds; 
};

/**
 * Returns a copy of the current entities floating-point position vector
 * @return A floating-point vector proportional to the current entities position
*/
sf::Vector2f Entity::getPosition() { 
  return position; 
};

/**
 * Returns a copy of the current entities floating-point scale vector
 * @return A floating-point vector proportional to the current entities scale
*/
sf::Vector2f Entity::getScale() { 
  return scale; 
};

/**
 * Sets the position of the current entity to a specific value
 * @param newPos The new floating-point position to be set for the current entity
*/
void Entity::setPosition(sf::Vector2f newPos) { 
  position = newPos; 
  bounds = sf::FloatRect(newPos + scale / 2.f, scale); 
};

/**
 * Sets the scale of the current entity to a specific value
 * @param newScale The new floating-point scale to be set for the current entity
*/
void Entity::setScale(sf::Vector2f newScale) { 
  scale = newScale; 
  bounds = sf::FloatRect(position, newScale); 
};

/**
 * Allows specific callbacks to be performed when the mouse hovers over the entity
*/
void Entity::onMouseHover() { 
  std::cout << "Mouse Hovered" << std::endl; 
}

/**
 * Allows the user to interact with the entity through the render window
*/
void Entity::interact() { 
  std::cout << "Interacted with " << name << std::endl;
};

/**
 * Updates the current entity
*/
void Entity::update() { };

/**
 * Renders the current entity on the appropriate render window
*/
void Entity::render(sf::RenderWindow &window) { };



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
 * Gets a pointer to a UI element from the manager
 * @param id The unique identifier for the entity being retrieved
 * @return A pointer to the entity at the index
*/
std::shared_ptr<Entity> EntityManager::getUIElement(std::string id) { 
  return uiElements[id];
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
 * Removes a UI element from the manager
 * @param index The stored index of the UI element to be removed
*/
void EntityManager::removeUIElement(std::string id) {
  uiElements.erase(id); 
};

/**
 * Returns the number of entities within the manager
 * @returns The current number of entities
*/
int EntityManager::size() { 
  return entities.size(); 
};

/**
 * Updates the mouse position with respect to internal entities
 * @param mousePos The position of the mouse
*/
void EntityManager::checkMousePosition(sf::Vector2i mousePos) {
  for (auto it = entities.begin(); it != entities.end(); it++) 
    it->second->checkMousePosition(mousePos); 
  for (auto it = uiElements.begin(); it != uiElements.end(); it++) 
    it->second->checkMousePosition(mousePos); 
};

/**
 * Interacts with applicable entities in the manager
*/
void EntityManager::interact() {
  for (auto it = entities.begin(); it != entities.end(); it++) 
    it->second->interact(); 
  for (auto it = uiElements.begin(); it != uiElements.end(); it++) 
    it->second->interact(); 
};

/**
 * Updates all entities in the manager
*/
void EntityManager::update() { 
  for (auto it = entities.begin(); it != entities.end(); it++) 
    it->second->update(); 
  for (auto it = uiElements.begin(); it != uiElements.end(); it++) 
    it->second->update(); 
};

/**
 * Renders all entities in the manager
 * @param window The render window
*/
void EntityManager::render(sf::RenderWindow &window) { 
  for (auto it = entities.begin(); it != entities.end(); it++) 
    it->second->render(window); 
  for (auto it = uiElements.begin(); it != uiElements.end(); it++) 
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
        addEntity<GraphicalEntity<sf::RectangleShape>>(name, shape, pos);

      // Creates a player instance
      } else if (color == sf::Color::Blue) {
        sf::CircleShape circleShape(pixelSize / 2);
        circleShape.setFillColor(sf::Color::Blue);
        definePlayer("Player");
        addEntity<GraphicalEntity<sf::CircleShape>>(playerKey, circleShape, pos);
      }
    }
  }
}

/**
 * Default destructor to clear all existing entities
*/
EntityManager::~EntityManager() { 
  entities.clear();
};