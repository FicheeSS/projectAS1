#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H
#include "Block.h"
#include <any>

class InteractiveObject : public Block {
private :
	int _h;
public:
	InteractiveObject(float x, float y, sf::Image* img, int h);
	bool effectPlayer(std::any* p);
};
#endif
