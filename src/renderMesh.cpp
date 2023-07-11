#include "mesh.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Splits string by delimiter an typecasts to specific value
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
      result.push_back(tempValue);
      start = index + 1;
    }
  } while (++index < ref.length());

  // Add final term to results
  std::stringstream typeCast(ref.substr(start, index));
  typeCast >> tempValue;
  result.push_back(tempValue);
  return result;
}

Point readPoint(const std::string &line) {
  std::istringstream stream(line);
  std::string prefix;
  float x, y, z;
  stream >> prefix >> x >> y >> z;
  return Point(x, y, z);
}

std::vector<Face> readFace(const std::string &line) {
  std::istringstream stream(line);
  std::vector<Face> formation;
  std::string substring;
  std::vector<int> indecies;
  int v, t, n; // vertex, texture, normal
  stream >> substring;

  while (stream) {
    stream >> substring;
    indecies = split<int>(substring, '/');
    formation.push_back(Face(indecies[0], indecies[1], indecies[2]));
  }

  return formation;
}

void Mesh::readFromFile(const char* filename) {
  std::string line;
  std::ifstream file(filename);

  if (!file) {
    std::cout << "Failed to read file: *" << filename << "*" << std::endl;
  } else {
    while (getline(file, line)) {
      if (line[0] == 'v') {
        if (line[1] == 't') {
          textures.push_back(readPoint(line));
        } else if (line[1] == 'n') {
          normals.push_back(readPoint(line));
        } else if (line[1] == ' ') {
          vertices.push_back(readPoint(line));
        }
      } else if (line[0] == 'f') {
        faces.push_back(readFace(line));
      }
    }
    file.close();
  }
}

void Mesh::troubleshoot() {
  std::cout << "Vertices: " << std::endl;
  for (auto vertex : vertices) vertex.print();
  std::cout << "Textures: " << std::endl;
  for (auto texture : textures) texture.print();
  std::cout << "Normals: " << std::endl;
  for (auto normal : normals) normal.print();
  std::cout << "Faces: " << std::endl;
  for (auto fullFaces : faces) {
    for (auto face : fullFaces) face.print();
    std::cout << std::endl;
  }
}

Mesh::Mesh(const char* filename) {
  readFromFile(filename);
  troubleshoot();
}
