#ifndef CHARACTER_H
#define CHARACTER_H
#include <tuple>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Commons.h"

class Character
{
protected:
	
	const float VITESSE = 1.5;

	float _x = 0.0f;
	float _y = 0.0f;
	sf::IntRect* _rect;
	std::vector<sf::Sprite*>* _sprite;
	std::vector<sf::Texture*>* _tex;
	float _accel = 0;
	int _maxX;

	enum places { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 };

	int _place = 0;
	sf::Vector2u _size;
	bool _canDoubleJump = false;
	bool _hasJumped = false;
	bool _hasDoubleJumped = false;
public :
	Character(int x, int y, std::vector<sf::Image*>* imgs);
	~Character();
	/**
	 * \brief Déplacement du charactère
	 * \param dir : std::tuple<DIRDEP, DIRDEP> (voir Univers.h)
	 * \param cols :  std::vector<bool> (voir Univers.h)
	 */
	void move(std::tuple<DIRDEP, DIRDEP> dir, std::vector<bool> cols);
	/**
	 * \brief Affichage du charactère
	 * \param rw : sf::RenderWindow* la fenètre d'affichage 
	 */
	void show(sf::RenderWindow* rw) { rw->draw(*_sprite->at(_place)); };


	//--------------------GETTER SETTER-------------------------//
	sf::IntRect getRect() { return *_rect; };
	float getX() { return _x; };
	float getY() { return _y; };
	void setMaxX(int x) { _maxX = x; };
	sf::Vector2u getSize() { return _size; };
	void setDoubleJump(bool jmp) { _canDoubleJump = jmp; };
	bool getDoubleJump() { return _canDoubleJump; };
};
#endif
