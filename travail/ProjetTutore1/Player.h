#pragma once
#include<SFML/Graphics.hpp>
#include "RessourcePack.h"
#include <SFML/Audio.hpp>
class Player{
private:
	int x;
	int y;
	sf::Sprite* sprite;
	sf::IntRect  rect;
	int maxX;
	int maxY;
	bool *collisionList ;
	std::vector<sf::Image*>* listImg;
	sf::Texture* tex;
	sf::SoundBuffer* sound;

public :
	//Correspond aux diff�rents sens dans lequel va se d�placer le player
	enum dir_t { NONE, LEFT, RIGHT, UP, DOWN };
	//Constructeur complet du Player
	Player(int, int, sf::IntRect ,std::vector<sf::Image*>&);
	//Methode d'affihcage du Player
	void show(sf::RenderWindow& window);
	//D�place le Player selon un tuple avec la direction <UP/DOWN/NONE,LEFT/RIGHT/NONE>
	inline sf::IntRect getRect() { return rect; }
	void move(std::tuple<dir_t,dir_t>&);
	void setTerrainBoundaries(int, int);
	inline void setCollide(bool *col) { collisionList = col; }
};