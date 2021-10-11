#pragma once
#include <string>
#include <vector>
#include "RessourcePack.h"
#include "Element.h"
class TerrainConstructor {
private:

public:
	TerrainConstructor(std::string filePath,RessourcePack &RP ,std::vector<Element> &tab);
};
