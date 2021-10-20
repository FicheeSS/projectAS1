#pragma once
#include <SFML/Graphics.hpp>
#include "TerrainElement.h"
class Tile : public TerrainElement{
protected:
	int x;
	int y;
	sf::IntRect  rect;
	bool isPhy;
	sf::Sprite *sprite ;
	//deplace l'élément 
	void move(int x, int y);
public:
	Tile();
};