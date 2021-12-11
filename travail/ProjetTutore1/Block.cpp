#include "Block.h"

Block::Block(int x, int y, sf::Image* img)
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

Block::~Block()
{
	delete(_sprite);
	delete(_tex);
	delete(_rect);	
}
