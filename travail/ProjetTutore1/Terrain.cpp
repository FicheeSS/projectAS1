#include "Terrain.h"

Terrain::Terrain(RessourcePack* rp)
{
	RP = rp;
	
}

void Terrain::loadTerrain(int level)
{
	terrain = TC.ConstructTerrainFromLevelFile(level, *RP);
	
}

std::vector<std::vector<TerrainElement*>*>* Terrain::getTerrain()
{
	return terrain;
}
