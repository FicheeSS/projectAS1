#include "TerrainConstructor.h"
#include "Player.h"
#include "Block.h"
#include "Commons.h"
#include "Levels.h"
#include "RessourcePack.h"
#include "InteractiveObject.h"
#include <iostream>
#include "Ennemi.h"

std::vector<sf::Image*>* TerrainConstructor::generatePersoImgInPlace(const std::string& s, RessourcePack* RP) const
{
	const auto img = new std::vector<sf::Image*>(4);
	imageVectorMemory->push_back(img);
	for (int i = 0; i < 4; i++)
	{
		try
		{
			img->at(0) = (RP->getPlayerImg(s + "LEFT"));
			img->at(1) = (RP->getPlayerImg(s + "RIGHT"));
			img->at(2) = (RP->getPlayerImg(s + "UP"));
			img->at(3) = (RP->getPlayerImg(s + "DOWN"));
		}
		catch (std::invalid_argument& e)
		{
			std::cerr << e.what() << std::endl;
			return nullptr;
		}
	}
	return img;
}

std::vector<Block*>* TerrainConstructor::ConstructTerrainFromLevelFile(int level, RessourcePack& RP, Player* oldp)
{
	std::vector<std::vector<int>>* lvl;
	imageVectorMemory = new std::vector<std::vector<sf::Image*>*>();
	switch (level)
	{
	case 1:
		lvl = &level1;
		break;
	case 2:
		lvl = &level2;
		break;
	default: //Ajouter ici si ils ont veux d'autres niveaux
		throw std::invalid_argument("Le niveau demande n'existe pas");
	}
	EnnemiList = new std::vector<Ennemi*>();
	sizeX = lvl->size();
	sizeY = lvl->at(0).size();
	Terrain = new std::vector<Block*>;
	for (uint32_t y = 0; y < lvl->size(); y++)
	{
		std::vector<int> line = lvl->at(y);
		for (uint32_t x = 0; x < line.size(); x++)
		{
			if (line[x] > 0 && line[x] < 100)
			{
				auto e = new Block(static_cast<float>(x * BLOCKWIDTH), static_cast<float>(y * BLOCKHEIGHT),
				                   RP.getImg(line[x]));
				Terrain->push_back(e);
			}
			else if (line[x] >= 100)
			{
				//si interactive object
				auto* it = new InteractiveObject(static_cast<float>(x * BLOCKWIDTH),
				                                 static_cast<float>(y * BLOCKHEIGHT), RP.getImg(line[x]), line[x]);
				Terrain->push_back(it);
			}
			else if (line[x] == -1)
			{
				
				p = new Player(static_cast<int>(x) * BLOCKWIDTH, static_cast<int>(y) * BLOCKHEIGHT,
						generatePersoImgInPlace("p", &RP), oldp);
			}
			else if (line[x] == -2)
			{
				EnnemiList->push_back(new Ennemi(static_cast<int>(x) * BLOCKWIDTH, static_cast<int>(y) * BLOCKHEIGHT,
				                                 generatePersoImgInPlace("e", &RP)));
			}
		}
	}
	return Terrain;
}

TerrainConstructor::TerrainConstructor()
= default;

TerrainConstructor::~TerrainConstructor()
{
	/*
	for (auto t : *Terrain) {
	    delete(t);
	}
	*/
	delete(Terrain);
	if (imageVectorMemory != nullptr)
	{
		for (auto tab : *imageVectorMemory)
		{
			delete(tab);
		}
		delete(imageVectorMemory);
	}
}
