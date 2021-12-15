#pragma once
#include "Block.h"
#include "Player.h"
#include <any>

class InteractiveObject : public Block {
private :
	int _h;
public:
	InteractiveObject(int x, int y, sf::Image* img, int h);
	//std::string _name = "IO";
	bool effectPlayer(Player* p);
};