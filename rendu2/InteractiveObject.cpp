#include "InteractiveObject.h"
#include <iostream>

InteractiveObject::InteractiveObject(float x, float y, sf::Image* img, int h)
	: Block(x, y, img) //super
{
	_h = h;
}

bool InteractiveObject::effectPlayer(Player *p)
{
	switch (_h) {
	case(100):
		p->setDoubleJump(true);
		return true;
		break;
	}
}
