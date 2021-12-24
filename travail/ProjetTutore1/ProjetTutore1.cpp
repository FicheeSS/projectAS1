#include <SFML/Graphics.hpp>
#include <iostream>
#include "RessourcePack.h"
#include <stdexcept>
#include <errno.h>
#include "Univers.h"
int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Projet Tutore Groupe 1");
    window.setFramerateLimit(144);
    sf::Image icon;
    if (icon.loadFromFile(".\\ico.png")) { // File/Image/Pixel
        sf::Vector2u s = icon.getSize();
        window.setIcon(s.x, s.y, icon.getPixelsPtr());
    }
    RessourcePack RP;
    Univers Univ(&RP,&window);
    if (argc > 0) {
        RP.setDefaultFolder(argv[0]);
    }
    Univ.animate();
    
    return EXIT_SUCCESS;
}
