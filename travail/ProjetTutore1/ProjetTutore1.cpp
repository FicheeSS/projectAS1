#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "RessourcePack.h"
#include "Univers.h"
int main(int argc, char* argv[])
{

    Menu* m = new Menu(R"(\ressources\menu\)");
    RessourcePack RP;
    /*if (argc > 0) {
        RP.setDefaultFolder(argv[0]);
    }
    */
    if(m->menu())
    {
        delete(m);
        sf::RenderWindow window(sf::VideoMode(1280, 720), "Projet Tutore Groupe 1", sf::Style::Default);
        window.setFramerateLimit(144);
        sf::Image icon;
        if (icon.loadFromFile(R"(.\ico.png)")) { // File/Image/Pixel
            sf::Vector2u s = icon.getSize();
            window.setIcon(s.x, s.y, icon.getPixelsPtr());
        }
        Univers Univ(&RP, &window);
        return Univ.animate();
    }else
    {
        return 0;
    }
    
}
