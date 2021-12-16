#pragma once
#include <tuple>
#include "Commons.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "Character.h"
class Player : public Character {
private:
	
public:
	Player(int x, int y, std::vector<sf::Image*>* imgs);
	~Player();

};