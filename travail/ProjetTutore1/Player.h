#pragma once
#include"Tile.h"
#include "Univers.h"
class Player{
private:
	int x;
	int y;
	sf::Sprite* sprite;
	sf::IntRect  rect;

public :
	enum dir_t { NONE, LEFT, RIGHT, UP, DOWN };
	Player(int, int, sf::IntRect ,const sf::Image&);
	void show(sf::RenderWindow& window);
	void move(std::tuple<dir_t,dir_t>);
};