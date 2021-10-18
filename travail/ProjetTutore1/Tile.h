#pragma once
#include <SFML/Graphics.hpp>

class Tile {
protected:
	int x;
	int y;
	sf::IntRect  rect;
	bool isPhy;
	sf::Sprite *sprite ;
	//deplace l'élément 
	void move(int x, int y);
public:
	std::string className = "Tile";
};