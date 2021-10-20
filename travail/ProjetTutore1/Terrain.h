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
	void loadTerrain(int level);
	std::vector<std::vector<TerrainElement*>*>* getTerrain();
	inline Player* getPlayer() {
		return TC.getPlayer();
	}
};