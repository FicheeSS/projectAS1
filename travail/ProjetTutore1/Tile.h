#pragma once
#include <SFML/Graphics.hpp>

class Tile {
protected:
	int x;
	int y;
	sf::IntRect  rect;
	bool isPhy;
	sf::Sprite *sprite = new sf::Sprite();
	//deplace l'élément 
	void move(int x, int y);
};