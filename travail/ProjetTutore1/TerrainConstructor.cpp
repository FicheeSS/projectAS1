#include "TerrainConstructor.h"



std::vector<std::vector<Element>>* TerrainConstructor::ConstructTerrain(std::string filePath, RessourcePack& RP)
{
    std::filesystem::path path(filePath);
  
    filePath = std::filesystem::absolute(filePath).string();
	std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // using printf() in all tests for consistency
            printf("%s", line.c_str());
        }
        file.close();
    }
	return Terrain;
}

TerrainConstructor::~TerrainConstructor() {
	delete(Terrain);
}