#ifndef MENU_H
#define MENU_H
#include<iostream>
#include<SFML/Graphics.hpp>

class Menu
{
    public:
        Menu(std::string path);
		~Menu();
        /** 
         * \brief Creer une fenètre de menu et renvoie si le joueur veux continuer
         * \return le joueur veut lancer le jeu
         */
        bool menu() const;

    protected:

    private:
        sf::Image* icon = new sf::Image();
        sf::Texture* texture = new sf::Texture();
        sf::Texture* boutonjouer = new sf::Texture();
        sf::Texture* boutonjouerclick = new sf::Texture();
        sf::Texture* boutonquitter = new sf::Texture();
        sf::Texture* boutonquitterclick = new sf::Texture();
        std::string _path;
};

#endif // MENU_H
