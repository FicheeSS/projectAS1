#include <SFML/Graphics.hpp>
#include <iostream>
#include "RessourcePack.h"
#include <stdexcept>
#include <errno.h>
#include "Univers.h"
int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Projet Tutoré Groupe 1");
    window.setFramerateLimit(144);
<<<<<<< HEAD
    sf::Image icon;
    if (icon.loadFromFile(".\\ico.png")) { // File/Image/Pixel
        sf::Vector2u s = icon.getSize();
        window.setIcon(s.x, s.y, icon.getPixelsPtr());
    }
=======

>>>>>>> a2219a782f2dd5b4c0a9fa8daa36aa5d01949aca
    RessourcePack RP;
    
    Univers Univ(&RP,&window);
    if (argc > 0) {
        RP.setDefaultFolder(argv[0]);
    }
<<<<<<< HEAD

=======
>>>>>>> a2219a782f2dd5b4c0a9fa8daa36aa5d01949aca
    Univ.animate();
    
    return EXIT_SUCCESS;
}
