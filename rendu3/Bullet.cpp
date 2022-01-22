#include "Bullet.h"



Bullet::Bullet(sf::Image* img, float positionX, float positionY, float directionX, float directionY) : _x(positionX),_y(positionY)
	,direction(new sf::Vector2f(directionX,directionY)),
	_tex(new sf::Texture())
{
	_tex->loadFromImage(*img);
	const sf::IntRect* texrect = new sf::IntRect(0, 0,img->getSize().x, img->getSize().y);// potentiel fuite mémoire
	_sprite = new sf::Sprite(*_tex,*texrect);
	_sprite->setPosition(_x, _y);
}

Bullet::~Bullet()
{
	delete(_sprite);
	delete(_tex);
}

sf::FloatRect Bullet::getBounds() const
{
	return _sprite->getGlobalBounds();
}

void Bullet::update() const
{
	//Met à jour le deplacement
	_sprite->move(vitesseTir * (*direction)); //ici "*" est une multiplication

}

void Bullet::render(sf::RenderTarget* target) const
{
	target->draw(*_sprite);
}

