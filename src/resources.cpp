/**
 * Generates a texture map of all textures to be imported
 * @author Lachlan Charteris
*/

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Mesh.hpp"

/**
 * Preloads common textures used throughout the project
 * @return A map with logical keys relating to a preloaded texture
*/
std::unordered_map<std::string, sf::Texture> generateTextureMap() {
  std::unordered_map<std::string, sf::Texture> textureMap;
  sf::Texture tempTexture;
  tempTexture.loadFromFile("res/Button.png");
  textureMap["BUTTON"] = sf::Texture(tempTexture);
  tempTexture.loadFromFile("res/ButtonHovered.png");
  textureMap["BUTTON_HOVERED"] = sf::Texture(tempTexture);
  tempTexture.loadFromFile("res/ButtonPressed.png");
  textureMap["BUTTON_PRESSED"] = sf::Texture(tempTexture);

  tempTexture.loadFromFile("res/Input.png");
  textureMap["INPUT"] = sf::Texture(tempTexture);
  tempTexture.loadFromFile("res/InputHovered.png");
  textureMap["INPUT_HOVERED"] = sf::Texture(tempTexture);
  tempTexture.loadFromFile("res/InputActive.png");
  textureMap["INPUT_ACTIVE"] = sf::Texture(tempTexture);
  tempTexture.loadFromFile("res/InputError.png");
  textureMap["INPUT_ERROR"] = sf::Texture(tempTexture);
  return textureMap;
}

/**
 * Preloads the color map used throughout the UI
 * @return A map with logical keys relating to UI colors
*/
std::unordered_map<std::string, sf::Color> generateColorMap() {
  std::unordered_map<std::string, sf::Color> colorMap;
  colorMap["BACKGROUND"] = sf::Color(10, 10, 10);
  colorMap["TEXT"] = sf::Color(200, 200, 200);
  colorMap["TOOLTIP"] = sf::Color::Black;
  colorMap["VERTICES"] = sf::Color(240, 240, 240);
  colorMap["FACES"] = sf::Color(200, 200, 200, 50);
  colorMap["ERROR"] = sf::Color(100, 0, 0);
  return colorMap;
}

/**
 * Preloads the mesh map used for rendering 3D meshes
 * @return A map with logical keys relating to 3D meshes
*/
std::unordered_map<std::string, Mesh> generateMeshMap() {
  std::unordered_map<std::string, Mesh> meshMap;
  meshMap["Test"] = Mesh("res/PersonModel.obj");
  meshMap["Cube"] = Mesh("res/Cube.obj");
  return meshMap;
}

/**
 * Preloads the arial font used throughout the UI
 * @return A font loaded from the arial ttf
*/
sf::Font loadArialFont() {
  sf::Font arialFont;
  arialFont.loadFromFile("res/arial.ttf");
  return arialFont;
}

/**
 * Provides a namespace containing all the global resources used throughout the project
*/
namespace resources {
  std::unordered_map<std::string, sf::Texture> TextureMap = generateTextureMap();
  std::unordered_map<std::string, sf::Color> ColorMap = generateColorMap();
  std::unordered_map<std::string, Mesh> MeshMap = generateMeshMap();
  sf::Font ArialFont = loadArialFont();
}
