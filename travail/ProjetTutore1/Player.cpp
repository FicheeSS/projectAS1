#include "Player.h"

Player::Player(int xp, int yp, sf::IntRect recte ,const sf::Image& imge)
{
	rect = recte;
	x = yp;
	y = xp;
	sf::Texture* tex = new sf::Texture();//Attention � l'allocation random
	tex->loadFromImage(imge);
	sprite = new sf::Sprite(*tex, rect);
	sprite->setTexture(*tex);
	sprite->setPosition(x, y);
	maxX = 0;
	maxY = 0;
	isOnTerrain = false;
}

void Player::show(sf::RenderWindow& window)
{
	window.draw(*sprite);

}

void Player::move(std::tuple<dir_t, dir_t>  &dir)
{
	switch (std::get<0>(dir)) {
	case UP :
		if (y > 0 ) {
			y--;
		}
		break;
	case DOWN:
		if (y < maxY - rect.height and !isOnTerrain) {
			y++;
		}
		break;
	}
	switch (std::get<1>(dir)) {
	case LEFT:
		if(x>0){
		x--;
		}
		break;
	case RIGHT:
		if (x < maxX - rect.width) {

			x++;
		}
		break;
	}
	sprite->setPosition(x, y);
	rect = sf::IntRect(x, y, rect.width, rect.height);
}

void Player::setTerrainBoundaries(int xb, int yb)
{
	maxX = xb;
	maxY = yb;
}
