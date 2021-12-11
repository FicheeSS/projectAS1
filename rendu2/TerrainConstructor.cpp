#include "TerrainConstructor.h"


std::vector<Block*>* TerrainConstructor::ConstructTerrainFromLevelFile(int level, RessourcePack& RP) {
    std::vector<std::vector<int>>* lvl;
    switch(level) {
    case 1 :
        lvl = &level1;
        break;
    default:       //Ajouter ici si ils ont veux d'autres niveaux
        throw std::invalid_argument("Le niveau demandé n'existe pas");
    }
    sizeX = lvl->size() ;
    sizeY = lvl->at(0).size();
    Terrain = new std::vector<Block*>; 
    for (uint32_t y = 0; y < lvl->size(); y++) {
        std::vector<int> line = lvl->at(y);
        for (uint32_t x = 0; x < line.size(); x++) {
            if (line[x] > 0) {
                Block* e = new Block(x * BLOCKWIDTH, y * BLOCKHEIGHT, RP.getImg(line[x]));
                Terrain->push_back(e);
            }
            else if (line[x] == -1) {
                p = new Player(x * BLOCKWIDTH, y * BLOCKHEIGHT, RP.getPlayerImgList());
            }
        }
        }
    return Terrain;
}

TerrainConstructor::TerrainConstructor()
{

}

TerrainConstructor::~TerrainConstructor() {
	delete(Terrain);
}