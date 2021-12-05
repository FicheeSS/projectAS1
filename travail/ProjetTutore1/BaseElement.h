#pragma once
class BaseElement {
public:
	enum TYPES { BASEELEMENT, BLOCK };
protected:
	int _x = 0;
	int _y = 0;
	BaseElement::TYPES type = BASEELEMENT;
public:
	inline TYPES getType() { return type; };
};