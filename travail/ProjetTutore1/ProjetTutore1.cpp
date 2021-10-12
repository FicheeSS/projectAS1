#include <SFML/Graphics.hpp>
#include <iostream>
#include "RessourcePack.h"
#include <stdexcept>
#include <errno.h>
#include "TerrainConstructor.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    RessourcePack RP;
    try{
        RP.generateImg("\\Ressources\\img");
    }
    catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
        return ENOENT;
    }

    TerrainConstructor TC;
    TC.ConstructTerrain("\\Ressources\\level1.dat", RP);
    //TC.ConstructTerrain("10 10 1 0 8 0 0 9", RP);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                ////std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                ////std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                break;
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return EXIT_SUCCESS;
}
