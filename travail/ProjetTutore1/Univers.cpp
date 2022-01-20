#include "Univers.h"
#include "Character.h"
#include "RessourcePack.h"
#include "Block.h"
#include "InteractiveObject.h"
#include "Player.h"
#include <iostream>
#include "Ennemi.h"
#include "Bullet.h"
int Univers::animate()
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
		return EXIT_FAILURE;
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
				return EXIT_SUCCESS;
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
				case sf::Keyboard::Space :

					if (std::get<1>(dir) != DIRDEP::NONE && p->getcanShoot()) {
						float dirX = 1;
						if (std::get<1>(dir) == DIRDEP::LEFT)
						{
							dirX = -1.f;
						}
						else if (std::get<1>(dir) == DIRDEP::RIGHT)
						{
							dirX = 1.f;

						}
						bullets->push_back(new Bullet(RP->getBulletImg(), p->getX(), p->getY(), dirX, 0.f));
					}
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
				return 0;
			}
			ctrlIsInUse = false;
			tabIsUse = false;
		}
#endif // DEBUG
		for (const auto en : *EnnemiList)
		{
			const std::vector<bool>* listCollision = collision(en);
			en->moveWithIa(*listCollision, sf::Vector2i(static_cast<int>(p->getX()), static_cast<int>(p->getY())));
			en->show(RW);
		}
		if (EnnemiToBeDeleted != nullptr) {
			for (uint32_t i = 0; i < EnnemiList->size(); i++)
			{
				if (EnnemiList->at(i) == EnnemiToBeDeleted)
				{
					EnnemiList->erase(i + EnnemiList->begin());
					EnnemiToBeDeleted = nullptr;
					break;
				}
			}
		}
		collision_bullet();
		for(auto b : *bullets)
		{
			b->update();
			b->render(RW);
		}
		for(auto hud : *hudList)
		{
			RW->draw(*hud);
		}
		const std::vector<bool>* listCollision = collision(p);
		if (listCollision != nullptr) {
			p->move(dir, *listCollision);
			p->show(RW);
		}else
		{
			nextLevel();
		}
		RW->display();

	}
	return 0;
}

std::vector<bool>* Univers::collision(Character* c)//block 50 fait tomber ds la map
{
	for (auto&& re : *res)
	{
		re = false;
	}
	for(auto b : *bullets)
	{
		if(b->getBounds().intersects(sf::Rect<float>(c->getRect())))
		{
			EnnemiToBeDeleted = reinterpret_cast<Ennemi*>(c);
		}
	}
	for (const auto t : *ter->getTerrain())
	{
		const auto e = static_cast<Block*>(t);
		if (e->collide(c->getRect()))
		{
#ifdef DEBUG
			e->colliding = true;
#endif // DEBUG

			const auto it = dynamic_cast<InteractiveObject*>(e);
			
			if (it != nullptr)
			{
				ACTION action = it->effect(reinterpret_cast<std::any*>(c));
				if (action == DEL)
				{
				remove_elem:
					//On supprime le block si besoin
					for (uint32_t i = 0; i < ter->getTerrain()->size(); i++) 
					{//On le cherche dans la liste du Terrain
						if (ter->getElementAtPos(static_cast<int>(i)) == it)
						{
							ter->getTerrain()->erase(ter->getTerrain()->begin() + static_cast<int>(i));
							break;
						}
					}

				}else if(action == JUMP){
					auto tex = new sf::Texture();
					tex->loadFromImage(*RP->getImgHud(0));
					tex->setSmooth(true);
					auto rec = new sf::IntRect(0,0,RP->getImgHud(0)->getSize().x, RP->getImgHud(0)->getSize().y);
					auto sp = new sf::Sprite(*tex,*rec);
					sp->setPosition(10, 10);
					hudList->push_back(sp);
					garbage.push_back(tex);
					garbage.push_back(rec);
					goto remove_elem;
				}else if(action == NEXTLEVEL){
					return nullptr;
				}else if (action == CANSHOOT)
				{
					auto tex = new sf::Texture();
					tex->loadFromImage(*RP->getImgHud(1));
					tex->setSmooth(true);
					auto rec = new sf::IntRect(0, 0, RP->getImgHud(0)->getSize().x, RP->getImgHud(0)->getSize().y);
					auto sp = new sf::Sprite(*tex, *rec);
					hudList->push_back(sp);
					garbage.push_back(tex);
					garbage.push_back(rec);
					sp->setPosition(10 + RP->getImgHud(0)->getSize().x, 10 );
					p->setCanShoot(true);
					goto remove_elem;
				}
				continue;
			}
			const int xb = static_cast<int>(e->getX());
			const int yb = static_cast<int>(e->getY());
			const int xp = static_cast<int>(c->getX());
			const int yp = static_cast<int>(c->getY());
			const sf::Vector2u size = c->getSize();
			if (yb + size.y <= yp + size.y / 3)
				res->at(TOP) = true;
			else if (static_cast<unsigned>(yb) >= yp + size.y / 4)
				res->at(COLDIR::BOTTOM) = true;
			else if (static_cast<unsigned>(xp) > xb + size.x / 4)
				res->at(LEFT) = true;
			else if (xp + size.x <= xb + size.x / 4)
				res->at(RIGHT) = true;
			else
				res->at(TOP) = true;
		}
	}
	// std::printf("Collision BOTTOM : %s, UP : %s ,LEFT : %s , RIGHT %s\n", res->at(COLDIR::BOTTOM) ? "true" : "false", res->at(COLDIR::TOP) ? "true" : "false", res->at(COLDIR::LEFT) ? "true" : "false", res->at(COLDIR::RIGHT) ? "true" : "false");
	return res;

}

void Univers::collision_bullet() const
{
	uint32_t toBeDeleted = -1;
	for(uint32_t i = 0 ; i < bullets->size();i++)
	{
		if(bullets->at(i)->getBounds().left  + bullets->at(i)->getBounds().width <= 0 || bullets->at(i)->getBounds().top + bullets->at(i)->getBounds().height <= 0 
			|| bullets->at(i)->getBounds().left >= ter->getSizeX() * BLOCKHEIGHT || bullets->at(i)->getBounds().top >=
			ter->getSizeY() * BLOCKWIDTH)
		{
			toBeDeleted = i;
			goto del;
			
		}
		for (const auto t : *ter->getTerrain())
		{
			if (t->collide(sf::IntRect(bullets->at(i)->getBounds())))
			{
				toBeDeleted = i ;
				goto del;
			}
		}

	}
del: 
	if(toBeDeleted != -1)
	{
		delete(bullets->at(toBeDeleted));
		bullets->erase(bullets->begin() + toBeDeleted);
		bullets->shrink_to_fit();
	}
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
		ter->loadTerrain(lvl,p);
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
	if (bullets != nullptr) {
		for (auto b : *bullets)
		{
			delete(b);
		}
		delete(bullets);
	}
	bullets = new std::vector<Bullet*>();
	backgroundTex = new sf::Texture();
	const auto si = sf::Vector2i(static_cast<int>(ter->getSizeY()) * BLOCKWIDTH,
	                             static_cast<int>(ter->getSizeX()) * BLOCKHEIGHT);
	backgroundTex->setSmooth(true);
	backgroundTex->setRepeated(true);
	backgroundTex->loadFromImage(*RP->getImgBackground(lvl), sf::IntRect(sf::Vector2i(0, 0), si));
	background = new sf::Sprite(*backgroundTex);
#pragma warning( push )
#pragma warning( disable : 4244)
	const sf::View View(sf::FloatRect(0, 0, static_cast<float>(ter->getSizeY()) * BLOCKWIDTH, static_cast<float>(ter->getSizeX()) * BLOCKHEIGHT));
#pragma warning( pop )
	//On met a jour le viewport en fonction de la nouvelle taille du terrain
	std::printf("Current Viewport : %d x %d \n", ter->getSizeY() * BLOCKWIDTH, ter->getSizeX() * BLOCKHEIGHT);
	RW->setView(View);
	p->setMaxX(static_cast<int>(ter->getSizeY()) * BLOCKWIDTH);
}

void Univers::cleanup() const
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

void Univers::shutdown() const
{
	cleanup();
	RW->close();
	if(currentMusic !=nullptr){
	currentMusic->stop();
	}
}


Univers::Univers(RessourcePack* rp, sf::RenderWindow* rw) : RP(rp), RW(rw)
{
	try
	{
		RP->generateImg("\\Ressources\\img");
		RP->generateAudioData("\\Ressources\\audio");
		//RP->generateBackgrounds("\\Ressources\\img\\backgrounds");
	}
	catch (std::invalid_argument &e)
	{
		std::cerr << e.what() << std::endl;
		shutdown();
		return;
	}
	hudList = new std::vector<sf::Sprite*>();
	loadTerrain(1);
}
