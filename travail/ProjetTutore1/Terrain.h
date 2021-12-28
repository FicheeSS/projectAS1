#ifndef TERRAIN_H
#define TERRAIN_H

#include<vector>
#include "TerrainConstructor.h"

class Player;
class RessourcePack;

class Terrain {
private:
	std::vector<Block*>* terrain = nullptr;
	RessourcePack* RP = nullptr;
	TerrainConstructor *TC = new TerrainConstructor();

public :
	Terrain(RessourcePack* RP);
	//Charge le terrain selon le niveau dans l'objet
	void loadTerrain(int level);
	~Terrain();
	//
	inline std::vector<Block*>* getTerrain() { return terrain; };
	inline Player* getPlayer() { return TC->getPlayer(); };
	inline Block* getElementAtPos(int x) { return terrain->at(x); };
	inline unsigned int getSize() { return terrain->size(); };
	inline unsigned int getSizeX() { return TC->sizeX; };
	inline unsigned int getSizeY() { return TC->sizeY; };
};
#endif
