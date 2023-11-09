/**
 * Provides functionality for mesh data objects
 * @author Lachlan Charteris
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Mesh.hpp"
#include "Projection.hpp"
#include "Resources.hpp"

/**
 * Default constructor for the Face structure
 * @param v The vertex of the new point
 * @param t The texture of the new point
 * @param n The normal of the new point
*/
Face::Face(int v, int t, int n) : vertex(v), texture(t), normal(n) { };

/**
 * Splits string into vector based on delimiters
 * @tparam T The template class of the output vector
 * @param ref The reference string being split
 * @param delimiter The delimiter to split by @def{" "}
 * @return A typecast vector of terms split from string
*/
template <class T>
std::vector<T> split(const std::string &ref, const char delimiter = ' ') {
  int start = 0, index = 0;
  std::vector<T> result;
  T tempValue;

  // Extract terms separated by delimiter
  do {
    if (ref[index] == delimiter || ref[index] == '\0') {
      if (start == index) tempValue = -1;
      else {
        std::stringstream typeCast(ref.substr(start, index));
        typeCast >> tempValue;
      }
      result.emplace_back(tempValue);
      start = index + 1;
    }
  } while (++index < ref.length());

  // Add final term to results
  std::stringstream typeCast(ref.substr(start, index));
  typeCast >> tempValue;
  result.emplace_back(tempValue);
  return result;
}

/**
 * Reads point data from a stringstream
 * @param line The line being interpreted - i.e. "v x y z"
 * @return The point object derived from the line
*/
sf::Vector3f readVertex(const std::string &line) {
  std::istringstream stream(line);
  std::string prefix;
  float x, y, z;
  stream >> prefix >> x >> y >> z;
  return sf::Vector3f(x, y, z);
}

/**
 * Reads face data from a stringstream which contains a dynamic length list of vertex, texture, and normal indicies comprising the face.
 * @param line A string describing the face in the form: "f iv1/it1/in1 iv2/it2/in2 ..."
 * @return A vector of sub-faces comprising a face
*/
std::vector<Face> readFace(const std::string &line) {
  std::istringstream stream(line);
  std::vector<Face> formation;
  std::string substring;
  std::vector<int> indecies;
  stream >> substring;

  while (stream) {
    stream >> substring;
    indecies = split<int>(substring, '/');
    formation.emplace_back(Face(indecies[0], indecies[1], indecies[2]));
  }

  return formation;
}



/**
 * Default constructor which reads a specified .obj file
 * @param filename The name of the .obj file
*/
Mesh::Mesh(const char* filename) {
  readFromFile(filename);
}

/**
 * Interprets a .obj file and stores it in the Mesh object
 * @param filename The name of the .obj file being interpreted
*/
void Mesh::readFromFile(const char* filename) {
  std::string line;
  std::ifstream file(filename);

  if (!file) {
    std::cout << "Failed to read file: *" << filename << "*" << std::endl;
  } else {
    while (getline(file, line)) {
      if (line[0] == 'v') {
        if (line[1] == 't') {
          textures.emplace_back(readVertex(line));
        } else if (line[1] == 'n') {
          normals.emplace_back(readVertex(line));
        } else if (line[1] == ' ') {
          vertices.emplace_back(readVertex(line));
        }
      } else if (line[0] == 'f') {
        faces.emplace_back(readFace(line));
      }
    }
    file.close();
  }
}

/**
 * Returns a vector of 3D positional vectors representing the vertices of the mesh
 * @return A vector of all 3D vertices comprising the mesh
*/
std::vector<sf::Vector3f> Mesh::getVertices() { 
  return vertices; 
};

/**
 * Projects all vertices from 3D to 2D with a set position and rotation
 * @param position The relative position of the mesh to the view instance
 * @param rotation The relative rotation of the mesh to the view instance
 * @param scaleFactor The factor with which to scale the vertices during projection @def{1}
 * @return A vector of all vertices projected to 2D space
*/
std::vector<sf::Vector2f> Mesh::getProjectedVertices(
  const sf::Vector3f &position, const sf::Vector3f &rotation, float scaleFactor
) {
  std::vector<sf::Vector2f> projectedVertices;
  Matrix rotationMatrix = getRotationMatrix(rotation), projectedMatrix;
  sf::Vector3f rotated;

  for (auto vertex : vertices) {
    // Rotate mesh in 3D space
    rotated = (rotationMatrix * vertex);
    rotated *= scaleFactor / position.z;
    rotated += position;
    projectedVertices.emplace_back(sf::Vector2f(rotated.x, rotated.y));
  } 
  return projectedVertices;
}

/**
 * Extracts a vector of points to be rendered, representing the vertices of the mesh
 * @param window The view window used to filter the vertices
 * @param projectedVertices A vector of vertices projected from 3D to 2D space
 * @return A vector of SFML circle shapes to be rendered which are contained within the screen
*/
std::vector<sf::CircleShape> Mesh::getRenderVertices(
  sf::RenderWindow &window, std::vector<sf::Vector2f> &projectedVertices
) {
  std::vector<sf::CircleShape> renderedVertices;
  sf::IntRect viewport = window.getViewport(window.getView());

  sf::CircleShape tempShape(2);
  tempShape.setFillColor(resources::ColorMap["VERTICES"]);

  for (auto vertex : projectedVertices) {
    if (viewport.contains(vertex.x, vertex.y)) {
      tempShape.setPosition(vertex - sf::Vector2f(2, 2)); // Center around vertex
      renderedVertices.emplace_back(tempShape);
    }
  }
  return renderedVertices;
}

/**
 * Extracts a vector of vertex edges to be rendered, representing the face edges of the mesh
 * @param window The view window used to filter the vertices
 * @param projectedVertices A vector of vertices projected from 3D to 2D space
 * @return A vector of SFML vertex arrays to be rendered which are contained within the screen
*/
std::vector<sf::VertexArray> Mesh::getRenderEdges(
  sf::RenderWindow &window, std::vector<sf::Vector2f> &projectedVertices
) {
  std::vector<sf::VertexArray> renderedEdges;
  sf::FloatRect viewport = (sf::FloatRect) window.getViewport(window.getView());
  sf::VertexArray vertexArray(sf::LinesStrip);

  // TODO: Remove duplicate edges being drawn from intersecting faces
  for (auto face : faces) {
    vertexArray.resize(face.size());
    for (int index = 0; index < face.size(); index++) {
      vertexArray[index].position = projectedVertices.at( face[index].vertex - 1 );
      vertexArray[index].color = sf::Color(resources::ColorMap["VERTICES"]);
    }

    if (vertexArray.getBounds().intersects(viewport))
      renderedEdges.emplace_back(vertexArray);
    vertexArray.clear();
  }

  return renderedEdges;
}

/**
 * Extracts a vector of convex shapes to be rendered, representing the faces of the mesh
 * @param window The view window used to filter the faces
 * @param projectedVertices A vector of vertices projected from 3D to 2D space
 * @return A vector of SFML convex hull shapes to be rendered which are contained within the screen
*/
std::vector<sf::ConvexShape> Mesh::getRenderFaces(
  sf::RenderWindow &window, std::vector<sf::Vector2f> &projectedVertices
) {
  std::vector<sf::ConvexShape> renderedFaces;
  sf::FloatRect viewport(window.getViewport(window.getView()));

  sf::ConvexShape tempShape;
  tempShape.setFillColor(resources::ColorMap["FACES"]);
  tempShape.setOutlineColor(resources::ColorMap["VERTICES"]);

  // TODO: Remove faces rendering behind other faces
  for (auto face : faces) {
    tempShape.setPointCount(face.size());
    for (int index = 0; index < face.size(); index++)
      tempShape.setPoint(index, projectedVertices.at( face[index].vertex - 1 ));
    if (tempShape.getLocalBounds().intersects(viewport))
      renderedFaces.emplace_back(tempShape);
  }

  return renderedFaces;
}