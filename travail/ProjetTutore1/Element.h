#pragma once
#include "Tile.h"
#include <stdexcept>
#include <tuple>
class Block :  public Tile {
private :
	sf::Sprite *sprite;
	bool isPhy = true;
public:
		std::string className = "Element";
		//Constructeur std
		Block(int x, int y, sf::IntRect recte, const sf::Image& img);
		//Affichage de l'�l�ment
		void show(sf::RenderWindow &window);
		//Renvoie un tuple avec la collision des deux �l�ments : revoie <-1,-1> si il n'y a pas de collision 
		std::tuple<int, int> collide(sf::IntRect);

};