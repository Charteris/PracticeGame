#ifndef RESOURCES
#define RESOURCES

/**
 * Provides template definitions for additional entities which can be used in the entity manager
 * @author Lachlan Charteris
*/

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Mesh.hpp"

std::unordered_map<std::string, sf::Texture> generateTextureMap();
std::unordered_map<std::string, sf::Color> generateColorMap();
std::unordered_map<std::string, Mesh> generateMeshMap();
sf::Font loadArialFont();

namespace resources {
  // Cannot be constant due to non-primitive types
  extern std::unordered_map<std::string, sf::Texture> TextureMap;
  extern std::unordered_map<std::string, sf::Color> ColorMap;
  extern std::unordered_map<std::string, Mesh> MeshMap; // Should support importing
  extern sf::Font ArialFont;

  // Provide constant resource values
  constexpr int TextSize = 14;
  constexpr int TooltipSize = 10;
  constexpr int TitleSize = 20;
}

#endif