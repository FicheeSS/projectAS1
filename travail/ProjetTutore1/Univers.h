#include "Terrain.h"
#include "Player.h"
#pragma once

class Univers {
private:
	std::tuple<Player::dir_t, Player::dir_t> dir = std::make_tuple(Player::dir_t::NONE, Player::dir_t::NONE); // O pour UP ou DOWN et 1 pour LEFT ou RIGHT
	Terrain *t;
	RessourcePack *RP;
	sf::RenderWindow* RW;
	std::vector<std::vector<TerrainElement*>*>* terrain;
	Player* p;
public:
	Univers(RessourcePack *rp,sf::RenderWindow*);
	void animate();
};