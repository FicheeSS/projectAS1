#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "entite.h"

using namespace std;

uint32_t const WINDOW_WIDTH=800;
uint32_t const WINDOW_HEIGHT=600;

int main()
{
    /// Ecrane principale
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Projet jeux video",sf::Style::Default);
    window.setFramerateLimit(144);
    bool entiteRight, entiteLeft, entiteUp, entiteDown = false;

    Entite joueur;
    sf::Texture textureKiwi;
    textureKiwi.loadFromFile("images/kiwi.png");
    sf::Sprite spriteKiwi(textureKiwi);


    /// Loop de jeux

    while (window.isOpen())
    {
        /// Sortie du jeux : fermeture de l'écrane
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        keyboardInput(entiteRight, entiteLeft, entiteUp, entiteDown, joueur, 2, true);

        std::cout << "   y : " << joueur.getY() << " // x : " << joueur.getX() << std::endl;


        /// Clear screen

        window.clear(sf::Color::White);
        window.draw(spriteKiwi);
        spriteKiwi.move(sf::Vector2f(joueur.getXDep(), joueur.getYDep() ));


        /// Draw the sprite


        /// Update the window

        window.display();
    }
    return 0;
}









