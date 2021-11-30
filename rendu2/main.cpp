#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Entite.h"
#include "Univers.h"

//using namespace sf;
using namespace std;

uint32_t const WINDOW_WIDTH=800;
uint32_t const WINDOW_HEIGHT=600;


int main()
{
    /// Ecrane principale

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Projet jeux video",sf::Style::Default);
    window.setFramerateLimit(60);
    bool entiteRight, entiteLeft, entiteUp, entiteDown = false;


    //-----------------------------------------------------------------------------------------------------------------------
    // On charge le sprite du personnage
    //-----------------------------------------------------------------------------------------------------------------------
    sf::Texture textureKiwi;
    textureKiwi.loadFromFile("images/kiwi.png");
    sf::Sprite spriteKiwi(textureKiwi);

    Entite joueur(spriteKiwi);

    //-----------------------------------------------------------------------------------------------------------------------
    // On charge le sol et d'autres blocs si nécessaire
    //-----------------------------------------------------------------------------------------------------------------------


    sf::Texture texDef;
    texDef.loadFromFile("images/bloc1.png");
    sf::Sprite spriteDef(texDef);

    Bloc sol(0,520,spriteDef,1.5,1);

    Bloc plateforme1(250,450,spriteDef,0.3,0.3);
// Bloc plateforme1(200,330,spriteDef);
    // Point de spawn du personnage
//    spriteKiwi.setPosition(200,200);

    vector <Bloc> plateformes;
    plateformes.push_back(plateforme1);
    plateformes.push_back(sol);



    ///----------------------------------------------------------------------------------------------------------------------
    /// Loop de jeux
    ///----------------------------------------------------------------------------------------------------------------------

    sf::Clock montreDuJeux;

    while (window.isOpen())
    {
        /// Sortie du jeux : fermeture de l'écrane
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        montreDuJeux.restart().asSeconds();

        /// Entrée des inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            entiteRight=true;
        }
        else
        {
            entiteRight=false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            entiteLeft=true;
        }
        else
        {
            entiteLeft=false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            entiteUp=true;
        }

        else
        {
            entiteUp=false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            entiteDown=true;
        }

        else
        {
            entiteDown=false;
        }


        /// Application des inputs au personnage

//        joueur.update(entiteUp,entiteDown,entiteLeft,entiteRight, sol);
        joueur.update(entiteUp,entiteDown,entiteLeft,entiteRight, sol,plateforme1);
//        joueur.update(entiteUp,entiteDown,entiteLeft,entiteRight,5,plateforme1, sol);
//        joueur.update(entiteUp,entiteDown,entiteLeft,entiteRight,5,plateformes);



        /// Sortie sur l'écrane de "contrôle"







    /// Calcul sens de movement axe Y :


//        std::cout << "  Sx :    " << joueur.getSprite().getPosition().x << "    Sy :   " << joueur.getSprite().getPosition().y <<

//       "   JXD :   " << joueur.getLimRelDroit() <<
//       "   PXD :   " << plateforme1.getCoteDroit() <<
//       "   JXG :   " << joueur.getLimRelGauche() <<
//       "   PXG :   " << plateforme1.getCoteGauche() <<
//       "   JYB :   " << joueur.getLimRelBase() <<
//       "   PYB :   " << plateforme1.getCoteBase() <<
//       "   JYH :   " << joueur.getLimRelSommet() <<
//       "   PYH :   " << plateforme1.getCoteSommet() <<

//       "   _colYB :   " << joueur.getCollisionYB() <<
//       "   _dernContColY :   " << joueur.getDernContColY() <<
//       "   _YDep :   " << joueur.getYDep() <<




//        "   _colliYB :   " << joueur.getCollisionYB() <<
//        "   _colliYH :   " << joueur.getCollisionYH() <<
//        "   _colliXG :   " << joueur.getCollisionXG() <<
//        "   _colliXD :   " << joueur.getCollisionXD() <<

//        std::endl;



        ///----------------------------------------------------------------------------------------------------------------------
        /// Clear screen
        ///----------------------------------------------------------------------------------------------------------------------

        window.clear(sf::Color::White);
        window.draw(joueur.getSprite());
        window.draw(sol.getSprite());
        window.draw(plateforme1.getSprite());



        ///----------------------------------------------------------------------------------------------------------------------
        /// Draw the sprite
        ///----------------------------------------------------------------------------------------------------------------------



        ///----------------------------------------------------------------------------------------------------------------------
        /// Update the window
        ///----------------------------------------------------------------------------------------------------------------------

        window.display();

    }
    return 0;
}









