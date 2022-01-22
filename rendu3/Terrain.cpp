#include "Terrain.h"
#include "InteractiveObject.h"

Terrain::Terrain(RessourcePack* rp) : RP(rp)
{
}

void Terrain::loadTerrain(int level, Player* p)
{
	terrain = TC->ConstructTerrainFromLevelFile(level, *RP,p);
}

Terrain::~Terrain()
{
	if (terrain != nullptr)
		for (const auto elem : *terrain)
		{
			if (elem != nullptr)
			{
				//selon le type d'élément on appel le bon destructeur
				auto it = dynamic_cast<InteractiveObject*>(elem);
				delete(it != nullptr ? it : elem);
			}
		}
	delete(TC);
}
