#pragma once
class TerrainElement {
public:
	enum TerrainElement_t {None , Tile, Element};
	inline TerrainElement_t getType() {
		return type;
	}
protected:
	TerrainElement_t type = None;
};