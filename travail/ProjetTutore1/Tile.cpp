#include "Tile.h"


void Tile::move(int xi, int yi)
{
	x = xi;
	y = yi;
}

Tile::Tile()
{
	type = TerrainElement::Tile;
}

