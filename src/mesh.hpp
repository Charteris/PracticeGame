#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>

// Defines a simple struct for storing vectors
struct Point {
  float x, y, z;
  Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { };
  void print() { std::cout << "(" << x << ", " << y << ", " << z << "), "; }
};

// Defines a simple struct for storing faces
struct Face {
  int vertex, texture, normal; // relevant indecies per vertex, texture, and normal vector
  Face(int v, int t, int n) : vertex(v), texture(t), normal(n) { };
  void print() { std::cout << "(" << vertex << ", " << texture << ", " << normal << "), "; }
};

// Defines a mesh object for rendering 3D meshes from .obj files
class Mesh {
private:
  // Vertices define the points comprising the object
  std::vector<Point> vertices;
  // Textures define the textures across faces
  std::vector<Point> textures;
  // Normals define the normal vectors used for rendering faces
  std::vector<Point> normals;
  // Faces define the points and normal vector comprising a face
  std::vector<std::vector<Face>> faces;
public:
  Mesh(const char* filename);
  void readFromFile(const char*);
  void troubleshoot();
  // void render();
};

#endif