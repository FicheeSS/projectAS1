#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <filesystem>
#include <stdexcept>
#define EXT ".png"
namespace fs = boost::filesystem;

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
