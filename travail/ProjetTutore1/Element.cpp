#include "Element.h"


Element::Element(int ye, int xe, sf::IntRect recte, const sf::Image & imge) {
	type = TerrainElement::Element;
	rect = recte;
	x = xe;
	y = ye;
	sf::Texture *tex =  new sf::Texture();//Attention à l'allocation random
	tex->loadFromImage(imge);
	sprite = new sf::Sprite(*tex,rect);
	sprite->setPosition(x, y);
}

void Element::show(sf::RenderWindow& window)
{
	window.draw(*sprite);

}



std::tuple<int, int> Element::collide(Element e)
{
	sf::IntRect intersec;
	return (e.rect.intersects(rect, intersec)) ? std::tuple<int, int>(intersec.left, intersec.top) : std::tuple<int,int>(-1,-1) ;
}
