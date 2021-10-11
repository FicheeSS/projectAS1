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
	* \brief prends un filepath correspondant a un fichier .dat tel que d�crit si dessous et place � l'aide de RP les �l�ment dans le tableau
	*
	* */

	/*
	* Les fichiers.dat sont formater de tel fa�on
	*example.dat
	* 10 10  //taille
	*  0 0 9 1 0 10  // definie deux �l�ment l'un sur l'autre � la postion 0 en bas � gauche

	*/
	std::vector<std::vector<Element>>* ConstructTerrain(std::string filePath, RessourcePack& RP);

	~TerrainConstructor();
};
