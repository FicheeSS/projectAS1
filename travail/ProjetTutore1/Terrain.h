#pragma once
#include<vector>
#include"TerrainElement.h"
#include <string>
#include "RessourcePack.h"
#include "TerrainConstructor.h"
class Terrain {
private:
	std::vector<std::vector<TerrainElement*>*>* terrain;
	RessourcePack* RP;
	TerrainConstructor TC;
public :
	Terrain(RessourcePack* RP);
	//Charge le terrain selon le niveau dans l'objet
	void loadTerrain(int level);
	~Terrain();
	//
	inline std::vector<std::vector<TerrainElement*>*>* getTerrain() { return terrain; }
	inline Player* getPlayer() {return TC.getPlayer();}
	inline TerrainElement* getElementAtPos(int x, int y) { return terrain->at(x)->at(y); }
	inline unsigned int getSizeofY() { return terrain->at(0)->size(); }
	inline unsigned int getSizeofX() { return terrain->size(); }
};