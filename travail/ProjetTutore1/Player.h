#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Character.h"
class Player : public Character {
private:
	
public:
	Player(int x, int y, std::vector<sf::Image*>* imgs);
	~Player();

};
#endif
