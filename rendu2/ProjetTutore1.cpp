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

    RessourcePack RP;
    
    Univers Univ(&RP,&window);
    if (argc > 0) {
        RP.setDefaultFolder(argv[0]);
    }
    Univ.animate();
    
    return EXIT_SUCCESS;
}
