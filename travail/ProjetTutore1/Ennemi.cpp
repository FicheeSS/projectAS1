#include"Ennemi.h"

void Ennemi::moveWithIa(std::vector<bool> cols, sf::Vector2i pos_j)
{
	int xJ = pos_j.x;
	std::tuple<DIRDEP, DIRDEP> dir;
	if (xJ > static_cast<int>(_x))
	{
		// le Joueur est a droite de l'ennemi
		dir = std::make_tuple(std::get<0>(dir), DIRDEP::RIGHT);
		if (cols.at(BOTTOM) && cols.at(COLDIR::RIGHT))
		{
			dir = std::make_tuple(DIRDEP::UP, std::get<1>(dir));
		}
	}
	else
	{
		dir = std::make_tuple(std::get<0>(dir), DIRDEP::LEFT);
		if (cols.at(BOTTOM) && cols.at(COLDIR::LEFT))
		{
			dir = std::make_tuple(DIRDEP::UP, std::get<1>(dir));
		}
	}
	move(dir, cols);

}
