#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <boost/algorithm/string.hpp>
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <regex>
#include <SFML/Audio.hpp>
#include <boost/regex.hpp>

#define IMGEXT ".png"
#define AUDEXT ".flac"


class RessourcePack {
private:
	std::vector<sf::Image*> *imgLoc;
	std::vector<sf::Image*> *imgLocPlayer;
	std::vector<std::tuple<std::string,sf::SoundBuffer*>>* soundList;
	std::vector<sf::Music*>* musicList;
	
public:
	enum places {LEFT=0,RIGHT=1,UP=2,DOWN=3};
	RessourcePack();
	void generateImg(std::string path);
	sf::Image* getImg(int n);
	//On vide les tableaux déclarés dans le HEAP
	~RessourcePack();
	inline std::vector<sf::Image*>* getPlayerImg() { return imgLocPlayer; };
	void generateAudioData(std::string path);
	sf::SoundBuffer* getSoundBufferByName(std::string);
	inline sf::Music* getLevelMusic(int lvl) 
	{ return (lvl >= musicList->size()) ? musicList->at(musicList->size() - 1) : musicList->at(lvl); };

};
