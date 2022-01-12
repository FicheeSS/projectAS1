#include "Univers.h"
#include "Character.h"
#include "RessourcePack.h"
#include "Block.h"
#include "InteractiveObject.h"
#include "Player.h"
#include <iostream>
#include "Ennemi.h"

void Univers::animate()
{
	currentMusic = RP->getLevelMusic(lvl - 1);
	try
	{
		currentMusic->play();
		currentMusic->setLoop(true);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		currentMusic->stop();
	}
	while (RW->isOpen())
	{
		RW->clear();
		if (background != nullptr)
		{
			RW->draw(*background);
		}
		sf::Event event{};
		while (RW->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed: [[unlikely]];
				shutdown();
				return;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Left:
					dir = std::make_tuple(std::get<0>(dir), DIRDEP::LEFT);
					break;
				case sf::Keyboard::Right:
					dir = std::make_tuple(std::get<0>(dir), DIRDEP::RIGHT);
					break;
				case sf::Keyboard::Up:
					dir = std::make_tuple(DIRDEP::UP, std::get<1>(dir));
					break;
				case sf::Keyboard::Down:
					dir = std::make_tuple(DIRDEP::DOWN, std::get<1>(dir));
					break;
#ifdef DEBUG
				case sf::Keyboard::LControl:
					ctrlIsInUse = true;
					break;
				case sf::Keyboard::Tab:
					tabIsUse = true;
					break;
#endif
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Right:
				case sf::Keyboard::Left:
					dir = std::make_tuple(std::get<0>(dir), DIRDEP::NONE);
					break;
				case sf::Keyboard::Down:
				case sf::Keyboard::Up:
					dir = std::make_tuple(DIRDEP::NONE, std::get<1>(dir));
					break;
#ifdef DEBUG
				case sf::Keyboard::LControl:
					ctrlIsInUse = false;
					break;
				case sf::Keyboard::Tab:
					tabIsUse = false;
					break;
#endif
				}
			}
		}
		for (auto t : *ter->getTerrain())
		{
			t->show(RW);
		}
#ifdef DEBUG
		if (ctrlIsInUse && tabIsUse)
		{
			lvl++;
			loadTerrain(lvl);
			if (!RW->isOpen())
			{
				return;
			}
			ctrlIsInUse = false;
			tabIsUse = false;
		}
#endif // DEBUG
		for (auto en : *EnnemiList)
		{
			const std::vector<bool>* listCollision = collision(en);
			en->moveWithIa(*listCollision, sf::Vector2i(static_cast<int>(p->getX()), static_cast<int>(p->getY())));
			en->show(RW);
		}
		std::vector<bool>* listCollision = collision(p);
		p->move(dir, *listCollision);
		p->show(RW);
		RW->display();
	}
}

std::vector<bool>* Univers::collision(Character* p) const
{
	for (auto&& re : *res)
	{
		re = false;
	}
	for (const auto t : *ter->getTerrain())
	{
		const auto e = static_cast<Block*>(t);
		if (e->collide(p->getRect()))
		{
#ifdef DEBUG
			e->colliding = true;
#endif // DEBUG

			const auto it = dynamic_cast<InteractiveObject*>(e);
			if (it != nullptr)
			{
				if (it->effectPlayer(reinterpret_cast<std::any*>(p)))
				{
					//On supprime le block si besoin
					for (uint32_t i = 0; i < ter->getTerrain()->size(); i++) 
					{//On le cherche dans la liste du Terrain
						if (ter->getElementAtPos(i) == it)
						{
							ter->getTerrain()->erase(ter->getTerrain()->begin() + i);
							break;
						}
					}
				}
				continue;
			}
			const int xb = static_cast<int>(e->getX());
			const int yb = static_cast<int>(e->getY());
			const int xp = static_cast<int>(p->getX());
			const int yp = static_cast<int>(p->getY());
			const sf::Vector2u size = p->getSize();
			if (yb + size.y <= yp + size.y / 3)
			{
				res->at(TOP) = true;
			}
			else if (static_cast<unsigned>(yb) >= yp + size.y / 4)
			{
				res->at(COLDIR::BOTTOM) = true;
			}
			else if (static_cast<unsigned>(xp) > xb + size.x / 4)
			{
				res->at(LEFT) = true;
			}
			else if (xp + size.x <= xb + size.x / 4)
			{
				res->at(RIGHT) = true;
			}

			else
			{
				res->at(TOP) = true;
			}
		}
	}
	// std::printf("Collision BOTTOM : %s, UP : %s ,LEFT : %s , RIGHT %s\n", res->at(COLDIR::BOTTOM) ? "true" : "false", res->at(COLDIR::TOP) ? "true" : "false", res->at(COLDIR::LEFT) ? "true" : "false", res->at(COLDIR::RIGHT) ? "true" : "false");
	return res;
}


void Univers::loadTerrain(int lvl)
{
	// on nettoie le terrain

	delete(ter);

	// on arrete puis on selectionne la bonne musique pour le niveau actuel
	if (currentMusic != nullptr)
	{
		currentMusic->stop();
		currentMusic = RP->getLevelMusic(lvl - 1);
		currentMusic->setLoop(true);
		currentMusic->play();
	}
	//On charge le nouveau terrain
	ter = new Terrain(RP);
	try
	{
		ter->loadTerrain(lvl);
	}
	catch (std::invalid_argument& e)
	{
		std::cerr << e.what() << std::endl;
		shutdown();
		return;
	}
	//On remplace le joueur
	delete(p);
	p = ter->getPlayer();
	//on charge le nouveau background
	delete(backgroundTex);
	delete(background);
	if (EnnemiList != nullptr)
	{
		for (auto en : *EnnemiList)
		{
			delete(en);
		}
		delete(EnnemiList);
	}
	EnnemiList = ter->getEnnemiList();
	backgroundTex = new sf::Texture();
	const auto si = sf::Vector2i(static_cast<int>(ter->getSizeY()) * BLOCKWIDTH,
	                             static_cast<int>(ter->getSizeX()) * BLOCKHEIGHT);
	backgroundTex->setSmooth(true);
	backgroundTex->setRepeated(true);
	backgroundTex->loadFromImage(*RP->getImgBackground(1), sf::IntRect(sf::Vector2i(0, 0), si));
	background = new sf::Sprite(*backgroundTex);
#pragma warning( push )
#pragma warning( disable : 4244)
	const sf::View View(sf::FloatRect(0, 0, ter->getSizeY() * BLOCKWIDTH, ter->getSizeX() * BLOCKHEIGHT));
#pragma warning( pop )
	//On met a jour le viewport en fonction de la nouvelle taille du terrain
	std::printf("Current Viewport : %d x %d \n", ter->getSizeY() * BLOCKWIDTH, ter->getSizeX() * BLOCKHEIGHT);
	RW->setView(View);
	p->setMaxX(ter->getSizeY() * BLOCKWIDTH);
}

void Univers::cleanup()
{
	// on nettoie le terrain
	delete(ter);
	if (currentMusic != nullptr)
	{
		currentMusic->stop();
		//delete(currentMusic); alsoft bug hors de notre controle ...
	}
	delete(p);
	delete(backgroundTex);
	delete(background);
	//delete(RP); //ne marche pas, pas important ne sert a rien dans ce cas
	delete(res);
}

void Univers::shutdown()
{
	cleanup();
	RW->close();
	currentMusic->stop();
}


Univers::Univers(RessourcePack* rp, sf::RenderWindow* rw)
{
	RW = rw;
	RP = rp;
	try
	{
		RP->generateImg("\\Ressources\\img");
		RP->generateAudioData("\\Ressources\\audio");
		//RP->generateBackgrounds("\\Ressources\\img\\backgrounds");
	}
	catch (std::invalid_argument e)
	{
		std::cerr << e.what() << std::endl;
		shutdown();
		return;
	}
	loadTerrain(1);
}
