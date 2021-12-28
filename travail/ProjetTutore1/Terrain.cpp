#include "Terrain.h"

Terrain::Terrain(RessourcePack* rp)
{
	RP = rp;

	
}

void Terrain::loadTerrain(int level)
{
	terrain = TC->ConstructTerrainFromLevelFile(level, *RP);
}

Terrain::~Terrain()
{
	if(terrain != nullptr)
	for (auto elem : *terrain) {
		if(elem != nullptr)
			delete(elem);
		
	}
}

