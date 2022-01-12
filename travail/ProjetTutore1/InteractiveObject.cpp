#include "InteractiveObject.h"
#include "Univers.h"
#include "Player.h"

InteractiveObject::InteractiveObject(float x, float y, sf::Image* img, int h)
	: Block(x, y, img), _h(h) //super
{
}

bool InteractiveObject::effectPlayer(std::any *a)
{
	Player* p = nullptr;
	switch (_h) {
	case(100):
		p = reinterpret_cast<Player*>(a);
		p->setDoubleJump(true);
		return true;
	case(101):

	default:
		return false;
	}
}

