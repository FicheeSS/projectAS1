#include "Character.h"

Character::Character(int x, int y, std::vector<sf::Image*>* imgs) : _x(x), _y(y), _tex(new std::vector<sf::Texture*>)
{
	_size = imgs->at(0)->getSize();
	_rect = new sf::IntRect(x, y, _size.x, _size.y);
	const auto texrect = new sf::IntRect(0, 0, _size.x, _size.y);
	_sprite = new std::vector<sf::Sprite*>(4);
	for (uint32_t i = 0; i < imgs->size(); i++)
	{
		auto tex = new sf::Texture();
		tex->loadFromImage(*imgs->at(i));
		tex->setSmooth(true);
		_tex->push_back(tex);
		_sprite->at(i) = new sf::Sprite(*tex, *texrect);
	}
	delete(texrect);
	_maxX = 0;
}

Character::~Character()
{
	delete(_sprite);
	delete(_tex);
	delete(_rect);
}

void Character::move(std::tuple<DIRDEP, DIRDEP> dir, std::vector<bool> cols)
{
	if (cols.at(BOTTOM))
	{
		//On est sur le sol 
		_accel = 0; // On verifie que l'accelération est bien nul
		_y -= 0.1f; // On remonte légérement vers le plafond pour eviter de fusionner avec le sol
		_place = DOWN;
		_hasJumped = false;
		_hasDoubleJumped = false;
	}
	else
	{
		_y += _accel; // sinon on accelere vers le sol
		_accel += DECEL;
		_place = DOWN;
	}
	if (cols.at(TOP))
	{
		if (_accel < 0)
		{
			_accel = 0;
		}
		_y += _accel + 5; // si on se tape la tête dans le plafond
		_accel += DECEL;
		_place = UP;
	}
	switch (std::get<0>(dir))
	{
	case DIRDEP::UP:
		if (cols[BOTTOM] && !cols[TOP])
		{
			//on est sur le sol et il n'y a pas de mur au dessus
			_accel = -MAXACC;
			_y += _accel;
			_place = UP;
			_hasJumped = true;
		}
		else if (_hasJumped && _canDoubleJump && !cols[TOP] && _accel >= -1 && !_hasDoubleJumped)
		{
			_hasDoubleJumped = true;
			_accel = -MAXACC;
			_y += _accel;
			_place = UP;
		}
		break;
	case DIRDEP::DOWN:
		break;
	}
	switch (std::get<1>(dir))
	{
	case DIRDEP::LEFT:
		if (_x > 0 && !cols[COLDIR::LEFT])
		{
			_x--;
			_place = LEFT;
		}
		break;
	case DIRDEP::RIGHT:
		if (!cols[COLDIR::RIGHT] && _x + BLOCKWIDTH < _maxX)
		{
			//TODO : Ajouter la vérification du max 
			_x++;
			_place = RIGHT;
		}
		break;
	}
	_sprite->at(_place)->setPosition(_x, _y);
	_rect->top = static_cast<int>(_y);
	_rect->left = static_cast<int>(_x);
}
