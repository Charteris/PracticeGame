
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Mesh.hpp"

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
sf::Vector3f readPoint(const std::string &line) {
  std::istringstream stream(line);
  std::string prefix;
  float x, y, z;
  stream >> prefix >> x >> y >> z;
  return sf::Vector3f(x, y, z);
}

/**
 * Reads face data from a stringstream which contains a dynamic length list of vertex, texture, and normal indicies comprising the face.
 * @param line The line being interpreted - i.e. "f iv1/it1/in1 iv2/it2/in2 ..."
 * @return A vector of sub-faces comprising a face
*/
std::vector<sf::Vector3f> readFace(const std::string &line) {
  std::istringstream stream(line);
  std::vector<sf::Vector3f> formation;
  std::string substring;
  std::vector<int> indecies;
  int v, t, n; // vertex, texture, normal
  stream >> substring;

  while (stream) {
    stream >> substring;
    indecies = split<int>(substring, '/');
    formation.emplace_back(sf::Vector3f(indecies[0], indecies[1], indecies[2]));
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
          textures.emplace_back(readPoint(line));
        } else if (line[1] == 'n') {
          normals.emplace_back(readPoint(line));
        } else if (line[1] == ' ') {
          vertices.emplace_back(readPoint(line));
        }
      } else if (line[0] == 'f') {
        faces.emplace_back(readFace(line));
      }
    }
    file.close();
  }
}

/**
 * Extracts a vertex of circle shapes to be rendered, representing the vertices of the mesh
 * @param position The position of the mesh in 3D space - relative to the camera
 * @param rotation The orientation of the mesh in 3D space (pitch/roll/yaw)
 * @return A vector of SFML circle shapes of vertices projected from 3D to 2D space
*/
std::vector<sf::CircleShape> Mesh::renderVertices(
  const sf::Vector3f &position, const sf::Vector3f &rotation
) {
  std::vector<sf::CircleShape> renderVertices;
  Matrix rotationMatrix = getRotationMatrix(rotation), projectedMatrix;
  sf::Vector3f rotated, projected, offset;
  float scale, distance = 2;

  sf::CircleShape tempShape(5);
  tempShape.setFillColor(sf::Color::Black);

  for (auto vertex : vertices) {
    // Rotate mesh in 3D space
    rotated = rotationMatrix * vertex;
    // Project onto 2D space
    // rotated /= (distance - rotated.z);
    // Add offset for position based on view angle
    rotated += (position - offset);

    tempShape.setPosition(rotated.x, rotated.y);
    renderVertices.emplace_back(tempShape);
  } 
  return renderVertices;
}

// std::vector<sf::ConvexShape> getFaces(
//   const sf::Vector3f &position, const sf::Vector3f &camera, const sf::Vector3f &rotation
// ) {
//   std::vector<sf::ConvexShape> renderVertices;
//   Matrix rotationMatrix = getRotationMatrix(rotation);
//   sf::Vector3f projectedVertex, offset = position - camera;

//   sf::ConvexShape 
// }