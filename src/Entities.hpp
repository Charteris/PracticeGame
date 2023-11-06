#ifndef ENTITIES
#define ENTITIES

/**
 * Provides template definitions for additional entities which can be used in the entity manager
 * @author Lachlan Charteris
*/

#include <math.h>

#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"
#include "Projection.hpp"
#include "Mesh.hpp"

/**
 * A graphical entity which can be drawn to the RenderWindow
 * @tparam S The type of graphic stored within the GraphicalEntity @def{sf::Sprite}
*/
template <typename S = sf::Sprite>
class GraphicalEntity : public Entity {
  protected:
    S graphic;

  public:
    GraphicalEntity(std::string, S);
    GraphicalEntity(std::string, S, sf::Vector2f);
    void setPosition(sf::Vector2f);
    void render(sf::RenderWindow&);
};

/**
 * An entity for rendering and updating 3D objects
*/
class MeshEntity : public Entity {
  protected:
    Mesh mesh;
    sf::Vector3f position3D;
    sf::Vector3f rotation;
    Camera *camera;

  public:
    MeshEntity(std::string, sf::Vector3f, Camera*, const char*, float scale=50);
    void rotate(sf::Vector3f rot) { rotation += rot; };
    void render(sf::RenderWindow&);
};

#endif