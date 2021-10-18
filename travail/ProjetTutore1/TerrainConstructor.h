#pragma once
#include <string>
#include <vector>
#include "RessourcePack.h"
#include "Element.h"
#include "Tile.h"
#include <fstream>
#include <filesystem>
#define BLOCKWIDTH 50
#define BLOCKHEIGHT 10
class TerrainConstructor {
private:
	std::vector<std::vector<Tile*>>* ConstructTerrainFromData(std::string,RessourcePack&);
	std::vector<std::vector<Tile*>>* Terrain ;
public:
	/*
	* \brief prends un filepath correspondant a un fichier .dat tel que décrit si dessous et place à l'aide de RP les élément dans le tableau
	*
	* */

	/*
	* Les fichiers.dat sont formater de tel façon (séparation par un seul espace entre les chiffres !!!)
	*example.dat
	* 10 10  //taille// 0 0 9 1 0 8  // definie deux élément l'un sur l'autre à la postion 0 en bas à gauche

	*/
	std::vector<std::vector<Tile*>>* ConstructTerrain(std::string filePath, RessourcePack& RP);
	~TerrainConstructor();
};
