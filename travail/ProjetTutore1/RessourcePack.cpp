#include "RessourcePack.h"

RessourcePack::RessourcePack(std::string path) {
	//Rechercher et charger les images dans le HEAP
}

std::vector<sf::Image*> RessourcePack::getImgList() {
	return imgList;
}

RessourcePack::~RessourcePack() {
	imgLoc.~vector();
	imgList.~vector();
}