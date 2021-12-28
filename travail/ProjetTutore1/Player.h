#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Character.h"
class Player : public Character {
private:
public:
	inline Player(int x, int y, std::vector<sf::Image*>* imgs) :Character(x, y, imgs) {};
};
#endif
