#ifndef ENTITIES
#define ENTITIES

#include <math.h>

#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"
#include "Mesh.hpp"

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