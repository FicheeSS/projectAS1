#include "Player.h"

Player::Player(int xp, int yp, sf::IntRect recte , std::vector<sf::Image*>& imge)
{
	rect = recte;
	x = yp;
	y = xp;
	tex = new sf::Texture();//Attention à l'allocation random
	listImg = &imge;
	tex->loadFromImage(*listImg->at(RessourcePack::RIGHT));
	sprite = new sf::Sprite(*tex, rect);
	sprite->setTexture(*tex);
	sprite->setPosition(x, y);
	maxX = 0;
	maxY = 0;
}

void Player::show(sf::RenderWindow& window)
{
	window.draw(*sprite);

}

void Player::move(std::tuple<dir_t, dir_t>  &dir)
{
	switch (std::get<0>(dir)) {
	case UP :
		if (y > 0 and !collisionList[1]) {
			y--;
			tex->loadFromImage(*listImg->at(RessourcePack::UP));
		}
		break;
	case DOWN:
		if (y < maxY - rect.height and !collisionList[0]) {
			y++;
			tex->loadFromImage(*listImg->at(RessourcePack::DOWN));

		}
		break;
	}
	switch (std::get<1>(dir)) {
	case LEFT:
		if(x>0 and !collisionList[3]){
		x--;
		tex->loadFromImage(*listImg->at(RessourcePack::LEFT));

		}
		break;
	case RIGHT:
		if (x < maxX - rect.width and !collisionList[2]) {

			x++;
			tex->loadFromImage(*listImg->at(RessourcePack::RIGHT));

		}
		break;
	}
	sprite->setTexture(*tex);
	sprite->setPosition(x, y);
	rect = sf::IntRect(x, y, rect.width, rect.height);
}

void Player::setTerrainBoundaries(int xb, int yb)
{
	maxX = xb;
	maxY = yb;
}

