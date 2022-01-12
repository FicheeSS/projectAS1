#include "Terrain.h"
#include "InteractiveObject.h"

Terrain::Terrain(RessourcePack* rp) : RP(rp)
{
}

void Terrain::loadTerrain(int level)
{
	terrain = TC->ConstructTerrainFromLevelFile(level, *RP);
}

Terrain::~Terrain()
{
	if (terrain != nullptr)
		for (const auto elem : *terrain)
		{
			if (elem != nullptr)
			{
				auto it = dynamic_cast<InteractiveObject*>(elem);
				if (it != nullptr)
				{
					delete(it);
				}
				else
				{
					delete(elem);
				}
			}
		}
	delete(TC);
}
