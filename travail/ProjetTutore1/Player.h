#pragma once
#include<SFML/Graphics.hpp>
class Player{
private:
	int x;
	int y;
	sf::Sprite* sprite;
	sf::IntRect  rect;

public :
	//Correspond aux différents sens dans lequel va se déplacer le player
	enum dir_t { NONE, LEFT, RIGHT, UP, DOWN };
	//Constructeur complet du Player
	Player(int, int, sf::IntRect ,const sf::Image&);
	//Methode d'affihcage du Player
	void show(sf::RenderWindow& window);
	//Déplace le Player selon un tuple avec la direction <UP/DOWN/NONE,LEFT/RIGHT/NONE>
	void move(std::tuple<dir_t,dir_t>&);
};