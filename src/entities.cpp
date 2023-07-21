
#include <math.h>

#include <SFML/Graphics.hpp>

#include "Entities.hpp"

/**
 * Default constructor to assign an id and load .obj file into Mesh object
 * @param id The unique id for the entity
 * @param pos The 3D position of the new entity
 * @param camera A reference to the camera object for orthographic projection
 * @param objFile The name of the .obj file
 * @param scale The scale factor for the resultant mesh @def{50}
*/
MeshEntity::MeshEntity(
  std::string id, sf::Vector3f pos, Camera *cam, const char *objFile, float scale
) {
  name = id;
  position3D = pos;
  position = sf::Vector2f(pos.x, pos.y);
  camera = cam;
  mesh.readFromFile(objFile);
  mesh.scaleMesh(scale);
}

/**
 * Renders the mesh object to the screen
 * @param window The render window to be drawn on
*/
void MeshEntity::render(sf::RenderWindow &window) {
  sf::Vector2u windowSize = window.getSize();
  sf::Vector3f camAngle = camera->getOrientation(), camPos = camera->getPosition();
  sf::Vector3f relativePos = position3D - camPos;
  // TODO: Only add by camera angle if the object is selected - updates the rotation of the mesh
  sf::Vector3f viewAngle = rotation + camAngle;

  std::vector<sf::CircleShape> vertices = mesh.renderVertices(relativePos, viewAngle);
  for (auto vertex : vertices)
    window.draw(vertex);
}