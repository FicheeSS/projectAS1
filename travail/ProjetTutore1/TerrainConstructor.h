#ifndef TERRAINCONSTRUCTOR_H
#define TERRAINCONSTRUCTOR_H
#include <vector>
#include <SFML/Graphics.hpp>
class RessourcePack;
class Block;
class Player;
class Ennemi;

class TerrainConstructor
{
private:
	Player* p = nullptr;
	std::vector<Block*>* Terrain = nullptr;
	std::vector<std::vector<sf::Image*>*>* imageVectorMemory = nullptr;
	std::vector<Ennemi*>* EnnemiList = nullptr;
	/**
 * \brief Génere un tableau de ptr d'image dans le bonne ordre pour l'affichage par le charactère
 * \param s : String correspondant au début de l'image correspondante
 * \param RP : RessourcePack
 * \return std::vector<sf::Image*>* ptr vers tableau de ptr d'image
 */
	std::vector<sf::Image*>* generatePersoImgInPlace(std::string s, RessourcePack* RP) const;
public:
	unsigned int sizeX = 0;
	unsigned int sizeY = 0;

	TerrainConstructor();
	Player* getPlayer() const
	{
		return p;
	}

	/**
	 * \brief Construit un Terrain depuis le numéro de celui-ci
	 * \param level : entier correspondant au niveau
	 * \param RP : RessourePack
	 * \return std::vector<Block*>* le Terrain ainsi généré
	 */
	std::vector<Block*>* ConstructTerrainFromLevelFile(int level, RessourcePack& RP);
	~TerrainConstructor();
	std::vector<Ennemi*>* getEnnemiList() const { return EnnemiList; };

};
#endif
