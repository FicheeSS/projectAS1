#pragma once
#include <tuple>
#include "Commons.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Character {
protected:
	int _x = 0;
	int _y = 0;
	sf::IntRect* _rect;
	std::vector <sf::Sprite*>* _sprite;
	std::vector<sf::Texture*>* _tex;
	float _accel = 0;
	int _maxX;
	enum places { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };
	int _place = 0;
	sf::Vector2u _size;
	bool _canDoubleJump = false;
	bool _hasJumped = false;
	bool _hasDoubleJumped = false;
public : 
	void move(std::tuple<DIRDEP, DIRDEP>, std::vector<bool>);
	inline void show(sf::RenderWindow* rw) { rw->draw(*_sprite->at(_place)); };
	inline sf::IntRect getRect() { return *_rect; };
	inline int getX() { return _x; };
	inline int getY() { return _y; };
	inline void setMaxX(int x) { _maxX = x; };
	inline sf::Vector2u getSize() { return _size; };
	inline void setDoubleJump(bool jmp) { _canDoubleJump = jmp; };

};