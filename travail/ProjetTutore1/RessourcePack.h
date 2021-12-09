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
	std::vector<sf::Image*> *backgroundImages;
	
public:
	enum places {LEFT=0,RIGHT=1,UP=2,DOWN=3};
	RessourcePack();
	//charge les images depuis le path specifié en paramtètre
	void generateImg(std::string path);
	void generateBackgrounds(std::string path);
	sf::Image* getImg(int n);
	//On vide les tableaux déclarés dans le HEAP
	~RessourcePack();
	sf::Image* getPlayerImg() { return imgLocPlayer->at(0); };
	std::vector<sf::Image*>* getPlayerImgList() { return imgLocPlayer; };
	//comme generateImg pour le son
	void generateAudioData(std::string path);
	//Va chercher le sound qui correspond au nom qu'on lui à donner comme fichier
	//EX : fichier "boing.flac" -> boing
	sf::SoundBuffer* getSoundBufferByName(std::string);
	inline sf::Image* getImgBackground(int n) { return backgroundImages->at(n - 1); };
	//renvoie la music pour le niveau donner en paramètre ou si le niveau est en dehors du tableau la music la plus proche
	inline sf::Music* getLevelMusic(int lvl) 
	{ return (lvl >= musicList->size()) ? musicList->at(musicList->size() - 1) : musicList->at(lvl); };

};
