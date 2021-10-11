#pragma once
#include <SFML/Graphics.hpp>

class Tile {
protected:
	int x;
	int y;
	sf::IntRect  rect;
	bool isPhy;
	sf::Image *img;
};