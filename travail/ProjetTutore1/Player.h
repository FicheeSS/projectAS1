#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Character.h"
class Player : public Character {
private:
	bool canShoot = false;
public:
	inline Player(int x, int y, std::vector<sf::Image*>* imgs,Player* p) :Character(x, y, imgs)
	{
		if(p!= nullptr)
		{
			canShoot = p->getcanShoot();
			setDoubleJump(p->getDoubleJump());
		}
	};
	inline bool getcanShoot() const { return canShoot; };
	inline void setCanShoot(bool shoot) { canShoot = shoot; };

};
#endif
