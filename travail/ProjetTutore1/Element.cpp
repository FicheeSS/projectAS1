#include "Element.h"


Element::Element(int xe, int ye, sf::IntRect recte, sf::Image* imge) {
	if (imge == nullptr) {
		throw std::runtime_error::runtime_error("Null pointer to img");
	}
	rect = recte;
	x = xe;
	y = ye;
	sf::Texture tex;
	tex.loadFromImage(*imge);
	sprite->setTextureRect(recte);
	sprite->setTexture(tex);
	sprite->setPosition(x, y);
}

void Element::show(sf::RenderWindow window)
{
	window.draw(*sprite);

}



std::tuple<int, int> Element::collide(Element e)
{
	sf::IntRect intersec;
	return (e.rect.intersects(rect, intersec)) ? std::tuple<int, int>(intersec.left, intersec.top) : std::tuple<int,int>(-1,-1) ;
}
