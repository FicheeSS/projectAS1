#include "TerrainConstructor.h"


// for string delimiter

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

std::vector<std::vector<Tile*>>* TerrainConstructor::ConstructTerrain(std::string filePath,  RessourcePack& RP)
{
    boost::filesystem::path full_path(boost::filesystem::current_path());
    filePath = full_path.string() + filePath;
    std::ifstream file(filePath);
        std::string data;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            data += line.c_str();
            printf("%s", line.c_str());
        }
        file.close();
    }
    //return new std::vector<std::vector<void*>>();
	return ConstructTerrainFromData(data,RP);
}


std::vector<std::vector<Tile*>>* TerrainConstructor::ConstructTerrainFromData(std::string fileData, RessourcePack& RP)
{
    std::vector<std::string> fileDataParsed = split(fileData, " ");
    std::tuple<int, int> size = std::tuple<int, int>(stoi(fileDataParsed[0]), stoi(fileDataParsed[1]));
    void* memoryAloc = malloc(sizeof(Tile) * std::get<0>(size) * std::get<1>(size));
    Terrain = new (memoryAloc) std::vector<std::vector<Tile*>>();
    uint32_t cpt = 2;
    for (uint32_t x = 0; x < std::get<0>(size); ++x) {
        std::vector<Tile*> subres;
        for (uint32_t y = 0; y < std::get<1>(size); ++y) {
            bool isInData = false;
            if(cpt != fileDataParsed.size()){
                 isInData = stoi(fileDataParsed[cpt + 1]) == x && stoi(fileDataParsed[cpt + 2]) == y;
                if (isInData) {
                    if (stoi(fileDataParsed[cpt]) > 0) {
                        sf::IntRect rect(stoi(fileDataParsed[cpt]), stoi(fileDataParsed[cpt + 1]), BLOCKHEIGHT, BLOCKWIDTH);
                        Element* e = new Element(stoi(fileDataParsed[cpt + 1])* BLOCKHEIGHT, stoi(fileDataParsed[cpt + 2])*BLOCKWIDTH, rect, RP.getImg(stoi(fileDataParsed[cpt])));
                        subres.push_back(e);
                    }
                    else {
                        //tmp
                        Tile *t=  new Tile();
                        subres.push_back(t);
                    }
                    cpt += 3;
                }
            }
            if(!isInData) {
                Tile* t = new Tile();
                subres.push_back(t);
            }
        }
        Terrain->push_back(subres);
    }
    return Terrain;
}

TerrainConstructor::~TerrainConstructor() {
	delete(Terrain);
}