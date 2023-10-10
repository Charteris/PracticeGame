#ifndef MESH
#define MESH

#include <iostream>
#include <vector>
#include <math.h>

#include <SFML/Graphics.hpp>

/**
 * Defines a Face struct used to store relative face information
*/
struct Point {
  int vertex, texture, normal;
  Point(int v, int t, int n) : vertex(v), texture(t), normal(n) { };
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
    std::vector<std::vector<Point>> faces;
    float scaleFactor = 1;
    
  public:
    Mesh() { };
    Mesh(const char*);
    void readFromFile(const char*, float scale=1);
    void updateScale(float scale) { scaleFactor = scale; };
    std::vector<sf::Vector3f> getVertices() { return vertices; };
    std::vector<sf::Vector2f> projectVertices(const sf::Vector3f&, const sf::Vector3f&);
    std::vector<sf::CircleShape> renderVertices(sf::RenderWindow&, std::vector<sf::Vector2f>&);
    std::vector<sf::VertexArray> renderEdges(sf::RenderWindow&, std::vector<sf::Vector2f>&);
    std::vector<sf::ConvexShape> renderFaces(sf::RenderWindow&, std::vector<sf::Vector2f>&);
};

/**
 * Simple Camera implementation for projecting 3D meshes
*/
class Camera {
  private:
    sf::Vector3f position;
    sf::Vector3f orientation;
  
  public:
    Camera() { };
    Camera(sf::Vector3f pos) : position(pos) { };
    Camera(sf::Vector3f pos, sf::Vector3f o) : position(pos), orientation(o) { };
    void moveCamera(sf::Vector3f velocity) { position += velocity; };
    void rotateCamera(sf::Vector3f rotation) { orientation += rotation; };
    sf::Vector3f getPosition() { return position; };
    sf::Vector3f getOrientation() { return orientation; };
    float getX() { return position.x; };
    float getY() { return position.y; };
    float getZ() { return position.z; };
    float getAngleX() { return orientation.x; };
    float getAngleY() { return orientation.y; };
    float getAngleZ() { return orientation.z; };
};

/**
 * Defines a simple Matrix struct
*/
struct Matrix {
  sf::Vector3f A, B, C;
  Matrix() { };
  Matrix(sf::Vector3f a,sf::Vector3f b,sf::Vector3f c) : A(a), B(b), C(c) { };
  Matrix operator*(const Matrix&);
  sf::Vector3f operator*(const sf::Vector3f&);
};

Matrix xProjection(float);
Matrix yProjection(float);
Matrix zProjection(float);
Matrix getRotationMatrix(sf::Vector3f);
Matrix getProjectionMatrix(sf::Vector3f);
float getMagnitude(sf::Vector3f);

#endif