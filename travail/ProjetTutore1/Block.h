#ifndef BLOCK_H
#define BLOCK_H
#include <SFML/Graphics.hpp>
#include <any>
#include "Commons.h"

class Block
{
private:
	float _x = 0;
	float _y = 0;
	//sf::IntRect* _rect = nullptr;
	sf::Sprite* _sprite = nullptr;
	sf::Texture* _tex = nullptr;
	sf::Image* img_ = nullptr;
public :
#ifdef DEBUG
	bool colliding = false;
#endif // DEBUG
	Block(float x, float y, sf::Image*);
	Block(Block* b);
	~Block();

	/**
	 * \brief Affichage du Block
	 * \param rw : sf::RenderWindow* la fenètre d'affichage 
	 */
	void show(sf::RenderWindow* rw);
	/**
	 * \brief Si le Block est en collision avec le rect en argv
	 * \param rect : sf::IntRect 
	 * \return bool
	 */
	bool collide(sf::IntRect rect) const;

	/**
	 * \brief Redéfinnision de l'opérateur == pour simplifier la vie
	 * \param b1 : &Block
	 * \param b2 : &Block
	 * \return Si les deux block sont les mêmes
	 */
	friend bool operator==(const Block& b1, const Block& b2);
	virtual ACTION effect(std::any* a);


	//-----------------------GETTER SETTER---------------------------//


	float getX() { return _x; };
	float getY() { return _y; };
};
#endif
