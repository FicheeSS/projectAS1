#include <SFML/Graphics.hpp>
#include <iostream>
#include "RessourcePack.h"
#include <stdexcept>
#include <errno.h>
#include "Univers.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Projet Tutoré Groupe 1");
    window.setVerticalSyncEnabled(true);//MDR ALED

    RessourcePack RP;
    try{
        RP.generateImg("\\Ressources\\img");
    }
    catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
        return ENOENT;
    }

    Univers Univ(&RP,&window);
    //TC.ConstructTerrain("10 10 1 0 8 0 0 9", RP);
    Univ.animate();

    return EXIT_SUCCESS;
}
