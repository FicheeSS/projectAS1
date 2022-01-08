#ifndef UNIVERS_H
#define UNIVERS_H
#include "Commons.h"
#include "Terrain.h"
#include "TerrainConstructor.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Character;
class Univers {
private:
	std::tuple<DIRDEP, DIRDEP> dir = std::make_tuple(DIRDEP::NONE, DIRDEP::NONE); // O pour UP ou DOWN et 1 pour LEFT ou RIGHT
	Terrain* ter;
	RessourcePack* RP;
	sf::RenderWindow* RW;
	#ifdef DEBUG
	bool ctrlIsInUse = false;
	bool tabIsUse = false;
	#endif
	Player* p;
	int lvl = 1 ;
	std::vector<bool>* res = new std::vector<bool>(4);
	sf::Sprite* background = nullptr;
	sf::Texture* backgroundTex = nullptr;
	sf::Music *currentMusic = nullptr;
	//Charge le terrain demander en parametre
	void loadTerrain(int lvl);
	//De-alloue les ressources utlisées par l'Univers
	void cleanup();
	
public:
	//Constructeur par defaut pour l'univers
	Univers(RessourcePack* rp, sf::RenderWindow*);
	void animate();
	inline void nextLevel() { lvl++; loadTerrain(lvl); };
	std::vector<bool>* collision(Character* p);
	enum posCol { BOTTOM =0,UP=1,ATLEFT=2,ATRIGHT=3 };
	void shutdown();

};
#endif