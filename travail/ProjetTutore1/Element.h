#pragma once
#include "Tile.h"
#include <stdexcept>
#include <tuple>
class Element : Tile {
private :
	bool isPhy = true;

public:
		//Constructeur std
		Element(int x, int y, sf::IntRect recte, sf::Image* img);
		//Affichage de l'élément
		void show();
		//Renvoie un tuple avec la collision des deux éléments : revoie <-1,-1> si il n'y a pas de collision 
		std::tuple<int, int> collide(Element);
};