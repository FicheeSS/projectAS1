#include "Player.h"

Player::Player(int x, int y, std::vector<sf::Image*>* imgs)
{
	_x = x;
	_y = y;
	_size = imgs->at(0)->getSize();
	_rect = new sf::IntRect(x, y,_size.x, _size.y);
	sf::IntRect* texrect = new sf::IntRect(0, 0, _size.x, _size.y);
	 _tex = new std::vector<sf::Texture*>;
	_sprite = new std::vector <sf::Sprite*>(4);
	for (uint32_t i = 0; i < imgs->size(); i++) {
		sf::Texture *tex = new sf::Texture();
		tex->loadFromImage(*imgs->at(i));
		tex->setSmooth(true);
		_tex->push_back(tex);
		_sprite->at(i) = new sf::Sprite(*tex, *texrect);
	}
	_maxX = 0;

}


Player::~Player()
{
	delete(_sprite);
	delete(_tex);
	delete(_rect);
}
