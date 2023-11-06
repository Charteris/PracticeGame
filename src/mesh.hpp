#ifndef MESH
#define MESH

/**
 * Provides template definitions for Mesh objects which can be imported from .obj files
 * @author Lachlan Charteris
*/

#include <iostream>
#include <vector>
#include <math.h>

#include <SFML/Graphics.hpp>

/**
 * Defines a Face struct used to store relative face information
*/
struct Face {
  int vertex, texture, normal;
  Face(int, int, int);
};

/**
 * Defines a mesh object for rendering 3D meshes from .obj files
*/
class Mesh {
  private:
    // Vertices define the points comprising the object
    std::vector<sf::Vector3f> vertices;
    // Textures define the textures across faces
    std::vector<sf::Vector3f> textures;
    // Normals define the normal vectors used for rendering faces
    std::vector<sf::Vector3f> normals;
    // Faces define the points and normal vector comprising a face
    std::vector<std::vector<Face>> faces;
    float scaleFactor = 1;
    
  public:
    Mesh() { };
    Mesh(const char*);
    void readFromFile(const char*, float scale=1);
    void updateScale(float);
    std::vector<sf::Vector3f> getVertices();
    std::vector<sf::Vector2f> projectVertices(const sf::Vector3f&, const sf::Vector3f&);
    std::vector<sf::CircleShape> renderVertices(sf::RenderWindow&, std::vector<sf::Vector2f>&);
    std::vector<sf::VertexArray> renderEdges(sf::RenderWindow&, std::vector<sf::Vector2f>&);
    std::vector<sf::ConvexShape> renderFaces(sf::RenderWindow&, std::vector<sf::Vector2f>&);
};

#endif