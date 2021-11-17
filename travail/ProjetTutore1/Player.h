#pragma once
#include<SFML/Graphics.hpp>
#include "RessourcePack.h"
#include <SFML/Audio.hpp>

#define ACCEL 3
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
	float yDelta = 0;
	bool canJump = true;
	unsigned int sizeX;
	unsigned int sizeY;

public :
	//Correspond aux différents sens dans lequel va se déplacer le player
	enum dir_t { NONE, LEFT, RIGHT, UP, DOWN };
	//Constructeur complet du Player
	Player(int, int, sf::IntRect ,std::vector<sf::Image*>&);
	//Methode d'affihcage du Player
	void show(sf::RenderWindow& window);
	//Déplace le Player selon un tuple avec la direction <UP/DOWN/NONE,LEFT/RIGHT/NONE>
	inline sf::IntRect getRect() { return rect; }
	void move(std::tuple<dir_t,dir_t>&);
	void setTerrainBoundaries(int, int);
	inline void setCollide(bool *col) { collisionList = col; }
	inline void setSize(int x, int y) { sizeX = x; sizeY = y; };
	inline int getSizeX() { return sizeX; };
	inline int getSizeY() { return sizeY; };
	~Player();
};