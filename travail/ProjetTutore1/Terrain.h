#ifndef TERRAIN_H
#define TERRAIN_H

#include<vector>
#include "TerrainConstructor.h"

class Player;
class RessourcePack;

class Terrain
{
private:
	std::vector<Block*>* terrain = nullptr;
	RessourcePack* RP = nullptr;
	TerrainConstructor* TC = new TerrainConstructor();

public :
	Terrain(RessourcePack* RP);
	~Terrain();

	/**
	 * \brief Charge le terrain du niveau passer en paramètre
	 * \param level : int le numero du niveau à charger
	 */
	void loadTerrain(int level);


	//-----------------------GETTER SETTER---------------------------//

	std::vector<Ennemi*>* getEnnemiList() const { return TC->getEnnemiList(); };
	std::vector<Block*>* getTerrain() const { return terrain; };
	Player* getPlayer() const { return TC->getPlayer(); };
	Block* getElementAtPos(int x) const { return terrain->at(x); };
	unsigned int getSize() const { return terrain->size(); };
	unsigned int getSizeX() const { return TC->sizeX; };
	unsigned int getSizeY() const { return TC->sizeY; };
};
#endif
