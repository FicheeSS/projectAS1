#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H
#include "Block.h"
#include <any>

class InteractiveObject : public Block
{
protected:
private :
	int _h;
public:
	InteractiveObject(float x, float y, sf::Image* img, int h);
	~InteractiveObject() = default;

	/**
	 * \brief Effect le player en fonction de _h 
	 * \param p : Object a caster dans le bon type selon _h
	 * \return : vrai - on doit supprimer le block | faux - on  doit le garder
	 */
	ACTION effect(std::any* p) ;
};
#endif
