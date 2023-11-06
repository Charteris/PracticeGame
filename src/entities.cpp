/**
 * Provides functionality for additional entities which can be used in the entity manager
 * @author Lachlan Charteris
*/

#include <math.h>

#include <SFML/Graphics.hpp>

#include "Entities.hpp"
#include "Projection.hpp"

/**
 * Constructor from drawable
 * @param id The identifier for the new graphical entity
 * @param g The drawable object
*/
template <typename S>
GraphicalEntity<S>::GraphicalEntity(std::string id, S g) {
  name = id;
  position = g.getPosition();
  scale = g.getScale();
  bounds = g.getLocalBounds();
}

/**
 * Constructor from position and drawable
 * @param id The identifier for the new graphical entity
 * @param g The drawable object
 * @param pos The 2D position vector
*/
template <typename S>
GraphicalEntity<S>::GraphicalEntity(std::string id, S g, sf::Vector2f pos) {
  g.setPosition(pos);
  GraphicalEntity<S>(id, g);
}

/**
 * Updates the position of the entity and its graphic and regenerates bounds
 * @param newPos The new position of the entity
*/
template <typename S>
void GraphicalEntity<S>::setPosition(sf::Vector2f newPos) {
  position = newPos;
  bounds = sf::FloatRect(newPos + scale / 2.f, scale);
  graphic.setPosition(newPos);
}

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
  mesh.readFromFile(objFile, scale);
}

/**
 * Renders the mesh object to the screen
 * @param window The render window to be drawn on
*/
void MeshEntity::render(sf::RenderWindow &window) {
  sf::Vector3f camAngle = camera->getOrientation(), camPos = camera->getPosition();

  // TODO: Only add by camera angle and position if the object is selected
  sf::Vector3f relativePos = position3D - camPos;
  sf::Vector3f viewAngle = rotation - camAngle;
  std::vector<sf::Vector2f> projectedVertices = mesh.projectVertices(relativePos, viewAngle);

  // Only render vertices which are within the window bounds
  std::vector<sf::ConvexShape> faces = mesh.renderFaces(window, projectedVertices);
  for (auto face : faces) {
    // Could be used for displaying edges but there are infinite perspective lines
    face.setOutlineThickness(0); 
    window.draw(face);
  }

  // Renders the edges of each face
  std::vector<sf::VertexArray> edges = mesh.renderEdges(window, projectedVertices);
  for (auto edge : edges) {
    window.draw(edge);
  }

  // Renders the points for each vertex
  std::vector<sf::CircleShape> vertices = mesh.renderVertices(window, projectedVertices);
  for (auto vertex : vertices) {
    vertex.setScale(1 / relativePos.z, 1 / relativePos.z);
    window.draw(vertex);
  }
}