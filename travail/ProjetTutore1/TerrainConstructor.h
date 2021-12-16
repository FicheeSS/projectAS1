#pragma once
#include <string>
#include <vector>
#include "RessourcePack.h"
#include <fstream>
#include <filesystem>
#include "Levels.h"
#include "Block.h"
#include "Commons.h"
#include "Player.h"
#include "InteractiveObject.h"
class TerrainConstructor {
private:
	Player* p = nullptr;
	std::vector<Block*>* Terrain = nullptr;

public:
	TerrainConstructor();
	/*

	*/
	inline Player* getPlayer() {
		return p;
	}
	//Renvoie le Terrain construit à l'aide du numéro du niveau
	std::vector<Block*>* ConstructTerrainFromLevelFile(int level,  RessourcePack& RP);
	~TerrainConstructor();
	unsigned int sizeX ;
	unsigned int sizeY = 0;
};
