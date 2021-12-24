#include "TerrainConstructor.h"


std::vector<Block*>* TerrainConstructor::ConstructTerrainFromLevelFile(int level, RessourcePack& RP) {
    std::vector<std::vector<int>>* lvl;
    switch(level) {
    case 1 :
        lvl = &level1;
        break;
    case 2:
        lvl = &level2;
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
            if (line[x] > 0 && line[x]<100) {
                Block* e = new Block(static_cast<float>(x * BLOCKWIDTH), static_cast<float>(y * BLOCKHEIGHT), RP.getImg(line[x]));
                Terrain->push_back(e);
            }
            else if(line[x] >= 100){ //si interactive object
                InteractiveObject *it = new InteractiveObject(static_cast<float>(x * BLOCKWIDTH), static_cast<float>(y * BLOCKHEIGHT), RP.getImg(line[x]), line[x]);
                Terrain->push_back(it);
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
    sizeX = 0;
    sizeY = 0;
}

TerrainConstructor::~TerrainConstructor() {
    for (auto t : *Terrain) {
        delete(t);
    }
	delete(Terrain);
}