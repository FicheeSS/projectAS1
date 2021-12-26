#pragma once
#pragma warning(push, 0)        
#include <boost/filesystem.hpp>
#pragma warning(pop)
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
	std::string defaultFolder = "";
	
public:
	enum places {LEFT=0,RIGHT=1,UP=2,DOWN=3};
	RessourcePack();
	//charge les images depuis le path specifié en paramètre 
	//throw std::invalid_argument si le path est vide
	void generateImg(std::string path);
	//charges les images depuis le path specifié en paramètre en vu de leur utilsation en background 
	//throw std::invalid_argument si le path est vide
	void generateBackgrounds(std::string path);
	//recupere dans le img celle à la position i 
	//throw std::invalid_argument si l'image n'existe pas 
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
	{ return ((unsigned int)lvl >= musicList->size()) ? musicList->at(musicList->size() - 1) : musicList->at(lvl); };
	inline void setDefaultFolder(std::string fold) { defaultFolder = fold; };
};
