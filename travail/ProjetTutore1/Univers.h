#ifndef UNIVERS_H
#define UNIVERS_H
#include "Commons.h"
#include "Terrain.h"
#include "TerrainConstructor.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Character;
class Ennemi;

class Univers
{
private:
	std::tuple<DIRDEP, DIRDEP> dir = std::make_tuple(DIRDEP::NONE, DIRDEP::NONE);
	// O pour UP ou DOWN et 1 pour LEFT ou RIGHT
	Terrain* ter = nullptr;
	RessourcePack* RP = nullptr;
	sf::RenderWindow* RW = nullptr;
#ifdef DEBUG
	bool ctrlIsInUse = false;
	bool tabIsUse = false;
#endif
	Player* p = nullptr;
	int lvl = 1;
	std::vector<bool>* res = new std::vector<bool>(4);
	sf::Sprite* background = nullptr;
	sf::Texture* backgroundTex = nullptr;
	sf::Music* currentMusic = nullptr;
	std::vector<Ennemi*>* EnnemiList = nullptr;
	/**
	 * \brief Charge le niveau dans l'Univers, exit si le niveau ne peut être charger
	 * \param lvl : int le niveau
	 */
	void loadTerrain(int lvl);
	//De-alloue les ressources utlisées par l'Univers
	void cleanup() const;

public:
	//Constructeur par defaut pour l'univers
	/**
	 * \brief Charge toutes les ressources nécessaire et charge le premier niveau
	 * \param rp : RessourcePack*
	 * \param rw : sf::RenderWindow* la fenètre d'affichage
	 */
	Univers(RessourcePack* rp, sf::RenderWindow* rw);

	/**
	 * \brief Boucle principale d'animation
	 * \return int : exit code
	 */
	int animate();

	/**
	 * \brief Incrémente le niveau courant et charge le suivant
	 */
	void nextLevel()
	{
		lvl++;
		loadTerrain(lvl);
	};

	/**
	 * \brief Calcul les collisions avec le Terrain 
	 * \param p : Character* un personnage avec lequel on veut check les collisions
	 * \return std::vector<bool>* liste des collisions selon posCol
	 */
	std::vector<bool>* collision(Character* p) const;

	enum posCol { BOTTOM =0, UP=1, ATLEFT=2, ATRIGHT=3 };

	/**
	 * \brief Ferme tous et nettoie les ressources du programme
	 */
	void shutdown() const;
};
#endif
