#include "header.hpp"

int main()
{
    // Simple circle rendering
    int width = 200, height = 200;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    int frames = 0;
    sf::Clock clock;
    clock.restart();
    while (window.isOpen())
    {
        // Support events
        manageEvents(window);

        // Clear screen, render items, and display new buffer
        window.clear();
        window.draw(shape);
        window.display();

        // Print frames per second
        ++frames;
        if (clock.getElapsedTime().asSeconds() >= 1) { 
            std::cout << "FPS: " << frames << std::endl;
            clock.restart();
            frames = 0;
        }
    }

    return 0;
}