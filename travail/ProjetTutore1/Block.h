#pragma once
#include <SFML/Graphics.hpp>
//#include "Commons.h"
#include "Player.h"
class Block {
private:
	int _x = 0;
	int _y = 0;
	sf::IntRect *_rect;
	sf::Sprite *_sprite;
	sf::Texture* _tex;
protected:
	Block();
public :
	//NEVER USE FOR DEBUG ONLY
	bool colliding = false;
	Block(int x, int y, sf::Image*);
	Block(Block *b);
	~Block();
	void show(sf::RenderWindow* rw);
	bool collide(sf::IntRect rect);
	inline int getX() { return _x; };
	inline int getY() { return _y; };
	friend bool operator==(const Block& b1, const Block& b2);
	virtual bool effectPlayer(Player* p);
};

