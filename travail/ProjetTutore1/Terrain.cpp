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
	for (auto elem : *terrain) {
			delete(elem);
		
	}
}

