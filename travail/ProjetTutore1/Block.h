#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>
#include <any>
#include "Commons.h"
class Block {
private:
	float _x = 0;
	float _y = 0;
	sf::IntRect *_rect;
	sf::Sprite *_sprite;
	sf::Texture* _tex;
protected:
	Block();
public :
	#ifdef DEBUG
	bool colliding = false;
	#endif // DEBUG
	Block(float x, float y, sf::Image*);
	Block(Block *b);
	~Block();
	void show(sf::RenderWindow* rw);
	bool collide(sf::IntRect rect);
	inline float getX() { return _x; };
	inline float getY() { return _y; };
	friend bool operator==(const Block& b1, const Block& b2);
	virtual bool effectPlayer(std::any* a);
};
#endif
