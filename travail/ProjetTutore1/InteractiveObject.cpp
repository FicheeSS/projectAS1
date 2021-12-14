#include "InteractiveObject.h"
#include <iostream>

InteractiveObject::InteractiveObject(int x, int y, sf::Image* img, int h)
	: Block(x, y, img) //super
{
	_h = h;
}

bool InteractiveObject::effectPlayer(Player* p)
{
	switch (_h) {
	case(100):
		std::cout<<p->getX();
		return true;
		break;
	}
}
