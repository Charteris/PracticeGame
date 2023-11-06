/**
 * Provides functionality for 3D camera and projection logic
 * @author Lachlan Charteris
*/

#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "Projection.hpp"

/**
 * Default empty constructor for Camera object
*/
Camera::Camera() { };

/**
 * Translates the Camera by a given 3D velocity vector
 * @param velocity The 3D floating-point velocity to be applied to the camera
*/
void Camera::moveCamera(sf::Vector3f velocity) { 
  position += velocity; 
};

/**
 * Rotates the camera by a given 3D rotation vector
 * @param rotation The 3D floating-point rotation vector to be applied to the camera
*/
void Camera::rotateCamera(sf::Vector3f rotation) { 
  orientation += rotation; 
};

/**
 * Returns a copy of the Cameras position vector
 * @return The floating-point 3D position vector of the Camera
*/
sf::Vector3f Camera::getPosition() { 
  return position; 
};

/**
 * Returns a copy of the Cameras rotation vector
 * @return The floating-point 3D rotation vector of the Camera
*/
sf::Vector3f Camera::getOrientation() { 
  return orientation; 
};



/**
 * Default empty constructor for matrix object
*/
Matrix::Matrix() { };

/**
 * Matrix object constructor from defined matrix rows
 * @param a The first matrix row
 * @param b The second matrix row
 * @param c The third matrix row
*/
Matrix::Matrix(sf::Vector3f a, sf::Vector3f b, sf::Vector3f c) : A(a), B(b), C(c) { };

/**
 * Computes the matrix multiplication between two 3x3 matrices
 * @param other The rvalue matrix being multiplied against
 * @return The resultant matrix
 * @overload
*/
Matrix Matrix::operator*(const Matrix &other) {
  return Matrix(
    sf::Vector3f(
      A.x*other.A.x + A.y*other.B.x + A.z*other.C.x,
      A.x*other.A.y + A.y*other.B.y + A.z*other.C.y,
      A.x*other.A.z + A.y*other.B.z + A.z*other.C.z
    ),
    sf::Vector3f(
      B.x*other.A.x + B.y*other.B.x + B.z*other.C.x,
      B.x*other.A.y + B.y*other.B.y + B.z*other.C.y,
      B.x*other.A.z + B.y*other.B.z + B.z*other.C.z
    ),
    sf::Vector3f(
      C.x*other.A.x + C.y*other.B.x + C.z*other.C.x,
      C.x*other.A.y + C.y*other.B.y + C.z*other.C.y,
      C.x*other.A.z + C.y*other.B.z + C.z*other.C.z
    )
  );
}

/**
 * Computes the matrix multiplication between 3x3 and 1x3 matrices
 * @param other The rvalue column vector being multiplied against
 * @return The resultant column vector
 * @overload
*/
sf::Vector3f Matrix::operator*(const sf::Vector3f &other) {
  return sf::Vector3f(
    A.x*other.x + A.y*other.y + A.z*other.z,
    B.x*other.x + B.y*other.y + B.z*other.z,
    C.x*other.x + C.y*other.y + C.z*other.z
  );
}

/**
 * Defines the x projection matrix for perspective
 * @param theta The x rotation angle in radians
 * @return The projection matrix in the x direction
*/
Matrix xProjection(float theta) { 
  return Matrix(
    sf::Vector3f(1, 0, 0), 
    sf::Vector3f(0, cos(theta), -sin(theta)), 
    sf::Vector3f(0, sin(theta), cos(theta))
  );
}

/**
 * Defines the y projection matrix for perspective
 * @param theta The y rotation angle in radians
 * @return The projection matrix in the y direction
*/
Matrix yProjection(float theta) { 
  return Matrix(
    sf::Vector3f(cos(theta), 0, sin(theta)), 
    sf::Vector3f(0, -1, 0), 
    sf::Vector3f(-sin(theta), 0, cos(theta))
  );
}

/**
 * Defines the y projection matrix for perspective
 * @param theta The y rotation angle in radians
 * @return The projection matrix in the y direction
*/
Matrix zProjection(float theta) { 
  return Matrix(
    sf::Vector3f(cos(theta), -sin(theta), 0), 
    sf::Vector3f(sin(theta), cos(theta), 0), 
    sf::Vector3f(0, 0, 1)
  );
}

/**
 * Computes the rotation matrix for perspective projection
 * <href=https://en.wikipedia.org/wiki/3D_projection>
 * @param rotation The rotation matrix to be applied
 * @return The pitch, roll, and yaw accounted rotation matrix
*/
Matrix getRotationMatrix(sf::Vector3f rotation) {
  return xProjection(rotation.x) * yProjection(rotation.y) * zProjection(rotation.z);
}

/**
 * Computes the projection matrix for perspective projection
 * <href=https://en.wikipedia.org/wiki/3D_projection>
 * @param dist The distance between the veiwing instance and the vertex
 * @return The homogeneous coordinates of the system
*/
Matrix getProjectionMatrix(sf::Vector3f dist) {
  return Matrix(
    sf::Vector3f(1, 0, dist.x / dist.z),
    sf::Vector3f(0, 1, dist.y / dist.z),
    sf::Vector3f(0, 0, 1 / dist.z)
  );
}

/**
 * Computes the magnitude of a 3D vector
 * @param vec The vector to compute the magnitude of
 * @return The resultant magnitude of the vector
*/
float getMagnitude(sf::Vector3f vec) {
  return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}