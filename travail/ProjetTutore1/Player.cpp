#include "Player.h"

Player::Player(int xp, int yp, sf::IntRect recte ,const sf::Image& imge)
{
	rect = recte;
	x = xp;
	y = yp;
	sf::Texture* tex = new sf::Texture();//Attention à l'allocation random
	tex->loadFromImage(imge);
	sprite = new sf::Sprite(*tex, rect);
	sprite->setTexture(*tex);
	sprite->setPosition(x, y);

}

void Player::show(sf::RenderWindow& window)
{
	window.draw(*sprite);

}

void Player::move(std::tuple<dir_t, dir_t>  &dir)
{
	switch (std::get<0>(dir)) {
	case UP :
		if (y > 0) {
			y--;
		}
		break;
	case DOWN:
		y++;
		break;
	}
	switch (std::get<1>(dir)) {
	case LEFT:
		if(x>0){
		x--;
		}
		break;
	case RIGHT:
		x++;
		break;
	}
	sprite->setPosition(x, y);
}
