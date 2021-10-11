#pragma once
#include <string>
#include <vector>
#include "RessourcePack.h"
#include "Element.h"
#include <fstream>
#include <filesystem>

class TerrainConstructor {
private:
	std::vector<std::vector<Element>>* Terrain = new std::vector<std::vector<Element>>;
public:
	/*
	* \brief prends un filepath correspondant a un fichier .dat tel que décrit si dessous et place à l'aide de RP les élément dans le tableau
	*
	* */

	/*
	* Les fichiers.dat sont formater de tel façon
	*example.dat
	* 10 10  //taille
	*  0 0 9 1 0 10  // definie deux élément l'un sur l'autre à la postion 0 en bas à gauche

	*/
	std::vector<std::vector<Element>>* ConstructTerrain(std::string filePath, RessourcePack& RP);

	~TerrainConstructor();
};
