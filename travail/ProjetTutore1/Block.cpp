#include "Block.h"

Block::Block(float x, float y, sf::Image* img)
{
	_x = x;
	_y = y;
	_rect = new sf::IntRect(x, y, BLOCKWIDTH, BLOCKHEIGHT);
	sf::IntRect *texrect = new sf::IntRect(0, 0, BLOCKWIDTH, BLOCKHEIGHT);
	_tex = new sf::Texture();
	_tex->loadFromImage(*img);
	_tex->setSmooth(true);
	_sprite = new sf::Sprite(*_tex, *texrect);
	//_sprite->setTexture(*_tex);
	_sprite->setPosition(x, y);
}

Block::Block(Block* b)
{
	_x = b->_x;
	_y = b->_y;
	_rect = new sf::IntRect(b->_x, b->_y, BLOCKWIDTH, BLOCKHEIGHT);
	sf::IntRect* texrect = new sf::IntRect(0, 0, BLOCKWIDTH, BLOCKHEIGHT);
	_tex = b->_tex;
	_sprite = b->_sprite;
	//_sprite->setTexture(*_tex);
	_sprite->setPosition(b->_x, b->_y);
}

void Block::show(sf::RenderWindow* rw) {
	// définit un rectangle de 120x50
	/*

	*/
	#ifdef DEBUG
	if (colliding) {
		sf::RectangleShape rectangle(sf::Vector2f(BLOCKWIDTH, BLOCKHEIGHT));
		rectangle.setPosition(sf::Vector2f(_x, _y));
		rw->draw(rectangle);
		colliding = false;
		return;
	}
	#endif // DEBUG
	rw->draw(*_sprite);
}

bool Block::collide(sf::IntRect rect)
{
	return _rect->intersects(rect);
}

bool Block::effectPlayer(Player* p)
{
	return false;
}


Block::~Block()
{
	delete(_sprite);
	delete(_tex);
	delete(_rect);	
}

bool operator==(const Block& b1, const Block& b2)
{
	return b1._x == b2._x && b1._y == b2._y;
}
