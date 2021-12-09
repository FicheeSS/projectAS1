#include "Player.h"

Player::Player(int x, int y, sf::Image* img)
{
	_x = x;
	_y = y;
	_rect = new sf::IntRect(x, y, BLOCKWIDTH, BLOCKHEIGHT);
	sf::IntRect* texrect = new sf::IntRect(0, 0, BLOCKWIDTH, BLOCKHEIGHT);
	_tex = new sf::Texture();
	_tex->loadFromImage(*img);
	_sprite = new sf::Sprite(*_tex ,* texrect);
	_maxX = 0;

}

void Player::move(std::tuple<DIRDEP, DIRDEP> dir, std::vector<bool> cols)
{
	if (cols.at(COLDIR::BOTTOM) ) { //On est sur le sol 
		_accel = 0; // On verifie que l'accelération est bien nul
		_y-=0.5f; // On remonte légérement vers le plafond pour eviter de fusionner avec le sol
	}else {
		_y += _accel; // sinon on accelere vers le sol
		_accel += DECEL;
	}
	if (cols.at(COLDIR::TOP)) {
		_y += _accel +2; // si on se tape la tête dans le plafond
		_accel += DECEL;
	}
	switch (std::get<0>(dir)) {
	case DIRDEP::UP:
		if (cols[COLDIR::BOTTOM] && !cols[COLDIR::TOP]) {//on est sur le sol et il n'y a pas de mur au dessus
			_accel = -MAXACC;
			_y += _accel;
		}
		break;
	case DIRDEP::DOWN:
 		break;

	}switch (std::get<1>(dir)) {
	case DIRDEP::LEFT:
		if (_x > 0 && !cols[COLDIR::LEFT]) {
			_x--;
		}
		break;
	case DIRDEP::RIGHT:
		if (!cols[COLDIR::RIGHT] && _x + BLOCKWIDTH < _maxX) { //TODO : Ajouter la vérification du max 
			_x++;
		}
		break;
	}
	_sprite->setPosition(_x, _y);
	_rect->top = _y;
	_rect->left = _x;

}

Player::~Player()
{
	delete(_sprite);
	delete(_tex);
	delete(_rect);
}
