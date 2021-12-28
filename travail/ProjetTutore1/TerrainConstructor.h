#ifndef TERRAINCONSTRUCTOR_H
#define TERRAINCONSTRUCTOR_H
#include <vector>

class RessourcePack;
class Block;
class Player;
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
#endif