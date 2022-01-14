#ifndef ENNEMI_H
#define ENNEMI_H
#include "Character.h"

class Ennemi : public Character
{
public:
	Ennemi(int x, int y, std::vector<sf::Image*>* imgs) : Character(x, y, imgs)
	{
	}

	void moveWithIa(std::vector<bool> cols, sf::Vector2i pos_j);
};

#endif // ! ENNEMI_H
