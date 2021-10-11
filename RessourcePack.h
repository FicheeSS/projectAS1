#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics/Image.hpp>
class RessourcePack {
private:
	std::vector<sf::Image*> imgList;
	std::vector<sf::Image> imgLoc;

public:
	RessourcePack(std::string path);
	std::vector<sf::Image*> getImgList();
	//On vide les tableaux déclarés dans le HEAP
	~RessourcePack();

};
