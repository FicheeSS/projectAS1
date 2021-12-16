#pragma once
#include "Block.h"
#include "Player.h"
#include <any>

class InteractiveObject : public Block {
private :
	int _h;
public:
	InteractiveObject(float x, float y, sf::Image* img, int h);
	//std::string _name = "IO";
	bool effectPlayer(Player* p);
};