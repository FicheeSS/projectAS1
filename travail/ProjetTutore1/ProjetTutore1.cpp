#include <SFML/Graphics.hpp>
#include <iostream>
#include "RessourcePack.h"
#include <stdexcept>
#include <errno.h>
#include "Univers.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Projet Tutoré Groupe 1");
    window.setFramerateLimit(144);
    
    RessourcePack RP;
    
    Univers Univ(&RP,&window);
    Univ.animate();
    
    return EXIT_SUCCESS;
}
