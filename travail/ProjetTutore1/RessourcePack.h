#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <regex>
#define EXT ".png"


class RessourcePack {
private:
	std::vector<sf::Image*> *imgLoc;
	std::vector<sf::Image*> *imgLocPlayer;
	
public:
	enum places {LEFT=0,RIGHT=1,UP=2,DOWN=3};
	RessourcePack();
	void generateImg(std::string path);
	sf::Image* getImg(int n);
	//On vide les tableaux déclarés dans le HEAP
	~RessourcePack();
	inline std::vector<sf::Image*>* getPlayerImg() { return imgLocPlayer; };

};
