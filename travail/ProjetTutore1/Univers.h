#pragma once*
#include "Terrain.h"
#include "TerrainConstructor.h"
#include<cmath>
class Univers {
private:
	std::tuple<DIRDEP, DIRDEP> dir = std::make_tuple(DIRDEP::NONE, DIRDEP::NONE); // O pour UP ou DOWN et 1 pour LEFT ou RIGHT
	Terrain* ter;
	RessourcePack* RP;
	sf::RenderWindow* RW;
	
	Player* p;
	int lvl = 1 ;
	std::vector<bool>* res = new std::vector<bool>(4);
	sf::Sprite* background = nullptr;
	sf::Texture* backgroundTex = nullptr;
	
public:
	//Constructeur par defaut pour l'univers
	Univers(RessourcePack* rp, sf::RenderWindow*);
	void animate();
	std::vector<bool>* collision(Player* p);
	void loadTerrain(int lvl);
	enum posCol { BOTTOM =0,UP=1,ATLEFT=2,ATRIGHT=3 };

};
