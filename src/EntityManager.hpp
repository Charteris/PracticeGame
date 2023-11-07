#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

/**
 * Provides template definitions for default entities and the entity manager
 * @author Lachlan Charteris
*/

#include <unordered_map>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

/**
 * A generic entity object for non-rendered requirements
*/
class Entity {
  protected:
    std::string name = "id";
    sf::Vector2f position = sf::Vector2f(0, 0);
    sf::Vector2f scale = sf::Vector2f(1, 1);
    sf::FloatRect bounds = sf::FloatRect(0, 0, 1, 1);
    bool isMouseInBounds = false;
    
  public:
    Entity();
    Entity(std::string);
    Entity(std::string, sf::Vector2f);
    Entity(std::string, sf::Vector2f, sf::Vector2f);
    void checkMousePosition(sf::Vector2i);
    bool intersects(Entity&);
    bool intersects(sf::FloatRect);
    bool contains(sf::Vector2f);
    bool contains(sf::Vector2i);
    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
    sf::Vector2f getScale();
    virtual void setPosition(sf::Vector2f);
    virtual void setScale(sf::Vector2f);
    virtual void onMouseHover();
    virtual void interact(sf::Mouse::Button, bool isMouseReleased = false);
    virtual void update();
    virtual void render(sf::RenderWindow&);
    virtual void troubleshoot();
};

/**
 * Defines the entity management system which stores and handles all entities
*/
class EntityManager {
  private:
    std::unordered_map<std::string, std::shared_ptr<Entity>> entities, uiElements;
    std::string playerKey = ""; // Duplicate reference to the player entity for ease of access

  public:
    template <typename Derived = Entity, typename... Args> 
    std::shared_ptr<Derived> addEntity(std::string, Args&&...);
    template <typename Derived = Entity, typename... Args> 
    std::shared_ptr<Derived> addUIElement(std::string, Args&&...);
    void definePlayer(std::string key) { playerKey = key; };
    std::shared_ptr<Entity> getPlayer();
    std::shared_ptr<Entity> getEntity(std::string);
    std::shared_ptr<Entity> getUIElement(std::string);
    void removePlayer();
    void removeEntity(std::string);
    void removeUIElement(std::string);
    int size();
    void checkMousePosition(sf::Vector2i);
    void interact(sf::Mouse::Button, bool isMouseReleased = false);
    void update();
    void render(sf::RenderWindow&);
    void addFromFile(const char*, float pixelSize=32, sf::Vector2f offset=sf::Vector2f(0, 0));
    ~EntityManager();
};

// Provide templated member function definition to avoid linking issues

/**
 * Instantiates a new entity in the manager
 * @tparam Derived The derived entity type being instantiated
 * @tparam Args The individual arguments contained in the parameter pack
 * @param id The unique identifier for the newly instantiated entity
 * @param args The parameter pack arguments for instantiating the entity
 * 
 * TODO: Add memory safeguards for duplicate keys instantiated
*/
template <typename Derived, typename... Args>
std::shared_ptr<Derived> EntityManager::addEntity(std::string id, Args&&... args) { 
  std::shared_ptr<Derived> newEntity = std::make_shared<Derived>(id, std::forward<Args>(args)...);
  entities.insert(std::make_pair(id, newEntity));
  return newEntity;
};

/**
 * Instantiates a new UI element in the manager
 * @tparam Derived The derived UI element type being instantiated
 * @tparam Args The individual arguments contained in the parameter pack
 * @param id The unique identifier for the newly instantiated UI element
 * @param args The parameter pack arguments for instantiating the UI element
 * 
 * TODO: Add memory safeguards for duplicate keys instantiated
*/
template <typename Derived, typename... Args>
std::shared_ptr<Derived> EntityManager::addUIElement(std::string id, Args&&... args) { 
  std::shared_ptr<Derived> newElement = std::make_shared<Derived>(id, std::forward<Args>(args)...);
  uiElements.insert(std::make_pair(id, newElement));
  return newElement;
};

#endif