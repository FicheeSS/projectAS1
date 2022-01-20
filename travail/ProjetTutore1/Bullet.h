#pragma once
#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::Vector2f* direction=nullptr;
	float vitesseTir = 2.f ;
	float _x = 0;
	float _y = 0;
	sf::Sprite* _sprite = nullptr;
	sf::Texture* _tex = nullptr;


public :
	//Bullet();
	Bullet(sf::Image* img,float positionX,float positionY, float directionX, float directionY);
	~Bullet();

	//Accesseur
	sf::FloatRect getBounds() const;
	void update() const;
	void render(sf::RenderTarget* target) const;
};

#endif // !BULLET_H
