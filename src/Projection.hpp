#ifndef PROJECTION
#define PROJECTION

/**
 * Provides template definitions for the camera and projection functions
 * @author Lachlan Charteris
*/

#include <iostream>
#include <vector>
#include <math.h>

#include <SFML/Graphics.hpp>

/**
 * Simple Camera implementation for projecting 3D meshes
*/
class Camera {
  private:
    sf::Vector3f position;
    sf::Vector3f orientation;
  
  public:
    Camera();
    void moveCamera(sf::Vector3f);
    void rotateCamera(sf::Vector3f);
    sf::Vector3f getPosition();
    sf::Vector3f getOrientation();
};

/**
 * Defines a simple Matrix struct
*/
struct Matrix {
  sf::Vector3f A, B, C;
  Matrix();
  Matrix(sf::Vector3f, sf::Vector3f, sf::Vector3f);
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