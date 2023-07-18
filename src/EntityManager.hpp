#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

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
    sf::Vector2f size = sf::Vector2f(1, 1);

  public:
    Entity() { };
    Entity(std::string id) : name(id) { };
    Entity(std::string id, sf::Vector2f pos) : name(id), position(pos) { };
    Entity(std::string id, sf::Vector2f pos, sf::Vector2f s) : name(id), position(pos), size(s) { };
    virtual void update() { };
    virtual void render(sf::RenderWindow &window) { };
    virtual void print() {
      std::cout << position.x << " " << position.y << " " << size.x << " " << size.y << std::endl;
    }
};

/**
 * A graphical entity which can be drawn to the RenderWindow
 * @tparam S The type of graphic stored within the GraphicalEntity @def{sf::Sprite}
*/
template <typename S = sf::Sprite>
class GraphicalEntity : public Entity {
  protected:
    S graphic;

  public:
    GraphicalEntity(std::string, sf::Vector2f, S);
    GraphicalEntity(std::string, sf::Vector2f, sf::Vector2f, S);
    bool intersects(const sf::FloatRect&);
    void render(sf::RenderWindow&);
};

/**
 * Defines the entity management system which stores and handles all entities
*/
class EntityManager {
  private:
    std::unordered_map<std::string, std::shared_ptr<Entity>> entities;
    std::string playerKey = ""; // Duplicate reference to the player entity for ease of access

  public:
    template <typename Derived = Entity, typename... Args> std::shared_ptr<Derived> addEntity(std::string, Args&&...);
    void definePlayer(std::string key) { playerKey = key; };
    std::shared_ptr<Entity> getPlayer();
    std::shared_ptr<Entity> getEntity(std::string);
    void removePlayer();
    void removeEntity(std::string);
    int size();

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

#endif