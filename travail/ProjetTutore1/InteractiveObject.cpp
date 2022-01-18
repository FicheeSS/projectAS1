#include "InteractiveObject.h"
#include "Univers.h"
#include "Player.h"

InteractiveObject::InteractiveObject(float x, float y, sf::Image* img, int h)
	: Block(x, y, img), _h(h) //super
{
}

bool InteractiveObject::effect( std::any *a )
{
	Player* p;
	Univers* u;
	switch (_h) {
	case(100):
		 p = reinterpret_cast< Player*>(a);
		if (p != nullptr) {
			p->setDoubleJump(true);
			return true;
		}
		break;
	case(101):
		 u = reinterpret_cast< Univers*>(a);
		if (u != nullptr) {
			u->nextLevel();
			return false;
		}
		break;
	default:
		return false;
	}
}

