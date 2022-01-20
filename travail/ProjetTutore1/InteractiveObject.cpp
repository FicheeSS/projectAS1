#include "InteractiveObject.h"
#include "Univers.h"
#include "Player.h"

InteractiveObject::InteractiveObject(float x, float y, sf::Image* img, int h)
	: Block(x, y, img), _h(h) //super
{
}

ACTION InteractiveObject::effect(std::any* a)
{
	Player* p;
	switch (_h) {
	case(100):
		 p = reinterpret_cast< Player*>(a);
		if (p != nullptr) {
			p->setDoubleJump(true);
			return DEL;
		}
		return ND;
	case(101):
		return NEXTLEVEL;
	case(102):
		return CANSHOOT;
	default:
		return ND;
	}
}

