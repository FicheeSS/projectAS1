#pragma once
#include <string>
#include <vector>
#include "RessourcePack.h"
#include "Element.h"
#include "Tile.h"
#include <fstream>
#include <filesystem>
#include "TerrainElement.h"
#include "Levels.h"
#include "Player.h"
#define BLOCKWIDTH 50
#define BLOCKHEIGHT 40
class TerrainConstructor {
private:
	Player* p;
	std::vector<std::vector<TerrainElement*>*>* Terrain ;
public:
	TerrainConstructor();
	/*

	*/
	inline Player* getPlayer() {
		return p;
	}
	std::vector<std::vector<TerrainElement*>*>* ConstructTerrainFromLevelFile(int level,  RessourcePack& RP);
	~TerrainConstructor();
};
