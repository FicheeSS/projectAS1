#pragma once
#include <tuple>
#include "Commons.h"
#include <vector>
#include <SFML/Graphics.hpp>
class Player {
private:
	int _x = 0;
	int _y = 0;
	sf::IntRect* _rect;
	sf::Sprite* _sprite;
	sf::Texture* _tex;
	float _accel = 0;
	
public:
	Player(int x, int y, sf::Image*);
	void move(std::tuple<DIRDEP, DIRDEP>, std::vector<bool>);
	inline void show(sf::RenderWindow* rw) {rw->draw(*_sprite);};	
	~Player();
	inline sf::IntRect getRect() { return *_rect; };
	inline int getX() { return _x; };
	inline int getY() { return _y; };
};