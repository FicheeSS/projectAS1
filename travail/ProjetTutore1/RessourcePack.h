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
	std::vector<sf::Image*> *imgList = new std::vector<sf::Image*>;
	std::vector<sf::Image> *imgLoc = new std::vector<sf::Image>;;

public:
	void generateImg(std::string path);
	sf::Image* getImg(int n);
	//On vide les tableaux d�clar�s dans le HEAP
	~RessourcePack();

};
