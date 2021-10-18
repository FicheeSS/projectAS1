#pragma once
#include "Tile.h"
#include <stdexcept>
#include <tuple>
class Element :  public Tile {
private :
	sf::Sprite *sprite;
	bool isPhy = true;
public:
		std::string className = "Element";
		//Constructeur std
		Element(int x, int y, sf::IntRect recte, const sf::Image& img);
		//Affichage de l'élément
		void show(sf::RenderWindow &window);
		//Renvoie un tuple avec la collision des deux éléments : revoie <-1,-1> si il n'y a pas de collision 
		std::tuple<int, int> collide(Element);

};