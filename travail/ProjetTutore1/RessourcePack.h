#ifndef RESSOURCEPACK_H
#define RESSOURCEPACK_H

#include <string>
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Audio.hpp>
#define IMGEXT ".png"
#define AUDEXT ".flac"


class RessourcePack
{
private:
	std::vector<sf::Image*>* imgLoc;
	std::vector<std::tuple<std::string, sf::Image*>>* imgLocPerso;
	std::vector<std::tuple<std::string, sf::SoundBuffer*>>* soundList;
	std::vector<sf::Music*>* musicList;
	std::vector<sf::Image*>* backgroundImages;
	std::string defaultFolder ;
	sf::Image* imgBullet;
	std::vector<sf::Image*>* hudImage;

public:
	RessourcePack();
	~RessourcePack();

	/**
	 * \brief Charge les images depuis le path specifi� en param�tre 
	 * \param path : String vers les ressources
	 * \throws std::invalid_argument lors d'une erreur acc�s ou si le path est vide
	 */
	void generateImg(std::string path);
	[[deprecated]]
	void generateBackgrounds(std::string path) const;
	/**
	 * \brief recupere dans le img celle � la position n
	 * \throws std::invalid_argument si l'image n'existe pas 
	 * \param n : int position de l'image
	 * \return sf::Image*
	 */
	sf::Image* getImg(int n);
	/**
	 * \brief Retourne le pointeur d'image avec le nom correspondant a s.
	 * \param s : String le nom de l'image
	 * \return sf::Image*
	 */
	sf::Image* getPlayerImg(std::string s) const;
	/**
	 * \brief Charge les fichier audio depuis le path specifi� en param�tre
	 * \param path : String vers les ressources
	 * \throws std::invalid_argument lors d'une erreur acc�s ou si le path est vide
	 */
	void generateAudioData(std::string path) const;
	/**
	 * \brief Va chercher le sound qui correspond au nom qu'on lui � donner comme fichier
	 * EX : fichier "boing.flac" -> boing
	 * \param name : String le nom de la piste audio rechercher
	 * \return sf::SoundBuffer*
	 */
	sf::SoundBuffer* getSoundBufferByName(std::string name);
	/**
	 * \brief Recup�re l'image qui correspond � l'image de background
	 * \param n : int le niveau 
	 * \return sf::SoundBuffer*
	 */
	sf::Image* getImgHud(int n) const
	{
		return hudImage->at(n);
	}
	sf::Image* getImgBackground(int n) const
	{
		return (static_cast<unsigned>(n) >= backgroundImages->size()) ?
			backgroundImages->at(backgroundImages->size() -1)
			:backgroundImages->at(n-1);
	};
	/**
	 * \brief renvoie la music pour le niveau donner en param�tre ou si le niveau est en dehors du tableau la music la plus proche
	 * \param lvl : int le niveau pour la musique
	 * \return sf::Music* 
	 */
	sf::Music* getLevelMusic(int lvl) const
	{
		return (static_cast<unsigned>(lvl) >= musicList->size())
			       ? musicList->at(musicList->size() - 1)
			       : musicList->at(lvl);
	};
	/**
	 * \brief Set un folder qui n'est pas dans l'arborecence directe pour les ressources
	 * \param fold : String path vers le fichier de ressources
	 */
	void setDefaultFolder(std::string fold) { defaultFolder = fold; };

	/**
	 * \brief Retourne le pointeur vers l'image du bullet 
	 * \return  sf::Image*
	 */
	inline sf::Image* getBulletImg() const { return imgBullet; };
};
#endif
