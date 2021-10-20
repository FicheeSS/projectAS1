#include "TerrainConstructor.h"


std::vector<std::vector<TerrainElement*>*>* TerrainConstructor::ConstructTerrainFromLevelFile(int level, RessourcePack& RP) {
    std::vector<std::vector<int>>* lvl;
    switch(level) {
    case 1 :
        lvl = &level1;
        break;
    default:
        throw std::invalid_argument("Le niveau demandé n'existe pas");
        break;
    //Ajouter ici si ils ont veux d'autres niveaux
    }
    Terrain = new std::vector<std::vector<TerrainElement*>*>;
    for (uint32_t x = 0; x < lvl->size(); x++) {
        std::vector<TerrainElement*>* ligne = new std::vector<TerrainElement*>;
        for (uint32_t y = 0; y < lvl->at(x).size();y++) {
            if (lvl->at(x)[y] > 0) {
                sf::IntRect rect(x, y, BLOCKWIDTH, BLOCKHEIGHT);
                Block* e = new Block(x * BLOCKHEIGHT, y * BLOCKWIDTH, rect, *RP.getImg(lvl->at(x)[y]));
                ligne->push_back(e);
            }
            else if (lvl->at(x)[y]==-1) {
                sf::IntRect rect(x, y, BLOCKWIDTH, BLOCKHEIGHT);
                 p = new Player(x * BLOCKHEIGHT, y * BLOCKWIDTH, rect, *RP.getImg(0));
            }
            else{
                TerrainElement* t = new TerrainElement();
                ligne->push_back(t);
            }
        }
        Terrain->push_back(ligne);
    }
    return Terrain;

}

TerrainConstructor::TerrainConstructor()
{

}

TerrainConstructor::~TerrainConstructor() {
	delete(Terrain);
}