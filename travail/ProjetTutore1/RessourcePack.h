#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <filesystem>
#include <stdexcept>
#include <iostream>
#define EXT ".png"


class RessourcePack {
private:
	std::vector<sf::Image> *imgLoc;

public:
	void generateImg(std::string path);
	sf::Image getImg(int n);
	//On vide les tableaux déclarés dans le HEAP
	~RessourcePack();

};
