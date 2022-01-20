#include "RessourcePack.h"
#pragma warning(push, 0)
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex/v5/regex.hpp>
#pragma warning(pop)
#include <iostream>
#include <regex>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

int getMaxFromPathStem(std::vector<boost::filesystem::path>* path)
{
	int max = 0;
	for (auto p : *path)
	{
		try
		{
			if (std::stoi(p.stem().string()) > max)
			{
				max = std::stoi(p.stem().string());
			}
		}
		catch (std::exception &e)
		{
		}
	}
	return max;
}

void RessourcePack::generateImg(std::string path)
{
	//Rechercher et charger les images dans le HEAP
	if (defaultFolder.empty())
	{
		boost::filesystem::path full_path(boost::filesystem::current_path());
		//std::cout << "Current path is : " << full_path << std::endl;
		path = full_path.string() + path;
	}
	else
	{
		path = defaultFolder + path;
	}
	std::vector<boost::filesystem::path> paths;

	if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
	{
		//on cherche tous les fichiers avec EXT dans path
		for (const auto& entry : boost::filesystem::recursive_directory_iterator(path))
		{
			if (is_regular_file(entry) && entry.path().extension() == IMGEXT)
			{
				paths.emplace_back(entry.path());
			}
		}
	}
	if (paths.empty()) throw std::invalid_argument("Aucune image n'ete trouve");
	std::sort(paths.begin(), paths.end());

	imgLoc = new std::vector<sf::Image*>(getMaxFromPathStem(&paths) + 1);
	for (boost::filesystem::path path : paths)
	{
		auto img = new sf::Image();
		if (!img->loadFromFile(path.string())) throw std::invalid_argument("File " + path.string() + "not found");
		// on lance une exeption si on n'arrive pas a charger l'image
		boost::regex nb("[0-9]*");
		boost::regex background(".*backgrounds.*");
		boost::regex bullet(".*bullet*.");
		boost::regex hud(".*hud*.");
		boost::regex font(".*font*.");
		boost::regex nont(".*nont*.");
		if (boost::regex_match(path.stem().string(), nb))
		{
			//C'est un block ou un bakcground
			if (boost::regex_match(path.string(), background))
			{
				//c'est un background
				backgroundImages->push_back(img); // On charge l'image dans le tableau d'image
			}
			else
			{
				imgLoc->at(std::stoi(path.stem().string())) = img; // On charge l'image dans le tableau d'image
			}
		}
		else
		{
			if(boost::regex_match(path.stem().string(), bullet)){
				imgBullet = img; 
			}
			else if (boost::regex_match(path.stem().string(), hud)) {
				hudImage->push_back(img);
			}
			else if(boost::regex_match(path.stem().string(),font))
			{
				generate_font(img);
			}else if(boost::regex_match(path.stem().string(),nont))
			{
				generate_nont(img);
			}
			else {
				//C'est une image de personnage
				imgLocPerso->push_back(std::make_tuple(path.stem().string(), img));
			}
		}
	}
	return;
}

[[deprecated]]
void RessourcePack::generateBackgrounds(std::string path) const
{
	//A fussioner avec generateIMG
	//Rechercher et charger les images dans le HEAP
	if (defaultFolder.empty())
	{
		boost::filesystem::path full_path(boost::filesystem::current_path());
		//std::cout << "Current path is : " << full_path << std::endl;
		path = full_path.string() + path;
	}
	else
	{
		path = defaultFolder + path;
	}
	std::vector<boost::filesystem::path> paths;

	if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
	{
		//on cherche tous les fichiers avec EXT dans path
		for (const auto& entry : boost::filesystem::recursive_directory_iterator(path))
		{
			if (is_regular_file(entry) && entry.path().extension() == IMGEXT)
			{
				paths.emplace_back(entry.path());
			}
		}
	}
	if (paths.empty()) throw std::invalid_argument("Aucune image n'ete trouve");
	std::sort(paths.begin(), paths.end());
	for (boost::filesystem::path path : paths)
	{
		auto img = new sf::Image();
		if (!img->loadFromFile(path.string())) throw std::invalid_argument("File " + path.string() + "not found");
		// on lance une exeption si on n'arrive pas a charger l'image
		boost::regex nb("[0-9]*");
		if (boost::regex_match(path.stem().string(), nb))
		{
			backgroundImages->push_back(img); // On charge l'image dans le tableau d'image
		}
	}
}

void RessourcePack::generateAudioData(std::string path) const
{
	if (defaultFolder.empty())
	{
		boost::filesystem::path full_path(boost::filesystem::current_path());
		//std::cout << "Current path is : " << full_path << std::endl;
		path = full_path.string() + path;
	}
	else
	{
		path = defaultFolder + path;
	}
	std::vector<boost::filesystem::path> paths;

	if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
	{
		//on cherche tous les fichiers avec EXT dans path
		for (const auto& entry : boost::filesystem::recursive_directory_iterator(path))
		{
			if (is_regular_file(entry) && entry.path().extension() == AUDEXT)
			{
				paths.emplace_back(entry.path());
			}
		}
	}
	if (paths.empty()) throw std::invalid_argument("Aucun Fichier Audio n'a �t� trouv�");
	std::sort(paths.begin(), paths.end());
	for (auto path : paths)
	{
		boost::regex nb("[0-9]*");
		if (boost::regex_match(path.stem().string(), nb))
		{
			auto music = new sf::Music;
			if (!music->openFromFile(path.string())) throw std::invalid_argument(
				"La musique " + path.string() + " n'a pas ete trouv�");
			musicList->push_back(music);
		}
		else
		{
			auto buffer = new sf::SoundBuffer;
			if (!buffer->loadFromFile(path.string()))throw std::invalid_argument(
				"Le fichier audio " + path.string() + " n'a pas ete trouv�");
			soundList->push_back(std::make_tuple(path.stem().string(), buffer));
		}
	}
}

sf::SoundBuffer* RessourcePack::getSoundBufferByName(std::string name)
{
	for (auto select : *soundList)
	{
		if (std::get<0>(select) == name)
		{
			return std::get<1>(select);
		}
	}
	return nullptr;
}

void RessourcePack::generate_font(sf::Image* imgFont)
{
	int x = 14;
	int y = 18;
	char c = 'A';
	const auto tex = new sf::Texture(); //Fuite memoire a gerer maybe
	tex->loadFromImage(*imgFont);
	for (int z = 0; z < 2; z++) {
		for (int i = 0; i < 14; i++)
		{
			tex->setSmooth(true);
			const auto rec = new sf::IntRect(x, y, sizeXChar, sizeYChar);
			auto sp = new sf::Sprite(*tex, *rec);
			fontSprite->insert({ c, sp });
			c++;
			x += 68;
		}
		y += 902;
		x = 14;
	}
}

void RessourcePack::generate_nont(sf::Image* imgFont)
{
	int x = 14;
	int y = 18;
	char c = '0';
	const auto tex = new sf::Texture(); //Fuite memoire a gerer maybe
	tex->loadFromImage(*imgFont);
		for (int i = 0; i < 10; i++)
		{
			tex->setSmooth(true);
			const auto rec = new sf::IntRect(x, y, sizeXChar, sizeYChar);
			auto sp = new sf::Sprite(*tex, *rec);
			fontSprite->insert({ c, sp });
			c++;
			x += 66;
	}
}

RessourcePack::RessourcePack()
{
	imgLoc = new std::vector<sf::Image*>;
	imgLocPerso = new std::vector<std::tuple<std::string, sf::Image*>>;
	soundList = new std::vector<std::tuple<std::string, sf::SoundBuffer*>>;
	musicList = new std::vector<sf::Music*>;
	backgroundImages = new std::vector<sf::Image*>;
	imgBullet = new sf::Image();
	hudImage = new std::vector<sf::Image*>;
}

sf::Image* RessourcePack::getImg(int n)
{
	if (imgLoc->at(n) == nullptr) throw std::invalid_argument("L'image n'a pas ete charger");
	return imgLoc->at(n);
};

RessourcePack::~RessourcePack()
{
	for (uint32_t i = 0; i < imgLoc->size(); i++)
	{
		delete(imgLoc->at(i));
	}
	for (uint32_t i = 0; i < imgLocPerso->size(); i++)
	{
		delete(std::get<1>(imgLocPerso->at(i)));
	}

	for (uint32_t i = 0; i < musicList->size(); i++)
	{
		delete(musicList->at(i));
	}
	for (uint32_t i = 0; i < soundList->size(); i++)
	{
		delete(std::get<1>(soundList->at(i)));
	}
	for (uint32_t i = 0; i < backgroundImages->size(); i++)
	{
		delete(backgroundImages->at(i));
	}
	delete(soundList);
	delete(musicList);
	delete(imgLocPerso);
	delete(imgLoc);
	delete(backgroundImages);
	delete(imgBullet);
}

std::vector<sf::Sprite*>* RessourcePack::generateText(std::string s, int x, int y)
{
	auto result = new std::vector<sf::Sprite*>();
	for(auto c : s )
	{
		c  = std::toupper(c);
		try
		{
			auto s = fontSprite->at(c);
			auto sp = new sf::Sprite(*s);
			sp->setPosition(x, y);
			result->push_back(sp);
		}
		catch (std::out_of_range)
		{
			std::cerr << c << " out of range" << std::endl;
		}
		x += sizeXChar - 5;
	}
	return  result;

}

sf::Image* RessourcePack::getPlayerImg(std::string s) const
{
	for (auto t : *imgLocPerso)
	{
		if (boost::algorithm::contains(std::get<0>(t), s))
		{
			return std::get<1>(t);
		}
	}
	throw new std::invalid_argument("L'image n'a pas ete trouv�");
}
