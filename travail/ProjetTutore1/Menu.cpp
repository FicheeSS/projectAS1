#include "Menu.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <SFML/Audio/Music.hpp>

Menu::Menu(std::string path) : _path(std::move(path))
{
	const boost::filesystem::path full_path(boost::filesystem::current_path());
	_path = full_path.string() + _path;


	if(!music->openFromFile(full_path.string()+R"(\Ressources\audio\menu.flac)"))
		throw new std::invalid_argument("La musique n'a pas été charger");
	//icon pour la barre des taches (logo du jeu)
	if (!icon->loadFromFile(_path + "img.png"))
		throw new std::invalid_argument("L'image n'a pas été charger");
	//load des textures a partir des images
	//background
	if (!texture->loadFromFile(_path + "BK2.png")) {
		throw new std::invalid_argument("L'image n'a pas été charger");
	}
	//bouton jouer
	if (!boutonjouer->loadFromFile(_path + "boutonjouer.png")) {
		throw new std::invalid_argument("L'image n'a pas été charger");
	}
	//bouton jouer quand la souris passe dessus
	if (!boutonjouerclick->loadFromFile(_path + "boutonjouerclick.png")) {
		throw new std::invalid_argument("L'image n'a pas été charger");
	}
	//bouton quitter
	if (!boutonquitter->loadFromFile(_path + "boutonquitter.png")) {
		throw new std::invalid_argument("L'image n'a pas été charger");
	}
	//bouton quitter qd la souris passe dessus
	if (!boutonquitterclick->loadFromFile(_path + "boutonquitterclick.png")) {
		throw new std::invalid_argument("L'image n'a pas été charger");
	}

}

Menu::~Menu()
{
	delete(icon);
	delete(texture);
	delete(boutonjouer);
	delete(boutonjouerclick);
	delete(boutonquitter);
	delete(boutonquitterclick);
}

bool Menu::menu() const
{


	//window deplacable mais non redimensionnable 
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Menu",sf::Style::Titlebar);
	window.setIcon(256,256,icon->getPixelsPtr());

	music->setLoop(true);
	music->play();
	//creation des sprites
	//sprite du background
	sf::Sprite bk;
	bk.setTexture(*texture);
	//bouton jouer
	sf::Sprite boutonJ;
	boutonJ.setTexture(*boutonjouer);
	//bouton jouer qd le souris passe dessus
	sf::Sprite boutonJC;
	boutonJC.setTexture(*boutonjouerclick);
	//bouton quitter
	sf::Sprite boutonQ;
	boutonQ.setTexture(*boutonquitter);
	//bouton quitter qd la souris passe dessus
	sf::Sprite boutonQC;
	boutonQC.setTexture(*boutonquitterclick);

	//set position des boutons
	sf::Vector2f a=window.getDefaultView().getCenter();
	boutonJ.setPosition(a.x - 118, a.y + 50);
	boutonQ.setPosition(a.x - 118, a.y + 130);
	boutonJC.setPosition(a.x - 118, a.y + 50);
	boutonQC.setPosition(a.x - 118, a.y + 130);

	//get des bounds des bouton pour verifier que la souris est dedans quand il click dessus
	sf::FloatRect jbound,qbound;
	jbound=boutonJ.getGlobalBounds();
	qbound = boutonQ.getGlobalBounds();
	
	//boolean qui seront true si la souris est sur le bouton (pour le draw du bon bouton)
	bool containJouer=false;
	bool containQuitter=false;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event)) {
			//si on press escape alors on ferme le jeu
			if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
			{
				return false;
			}
			//si la souris est sur le bouton jouer
            if (jbound.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
				containJouer = true; // pour afficher le bon bouton dans le draw plus loin
				//si il click
				if(event.type == sf::Event::MouseButtonPressed){
					music->stop();
                    return true;
                }
            }else {
				containJouer = false;
            }
			//si il est sur le bouton quitter
            if(qbound.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))){
				containQuitter = true;
                if(event.type == sf::Event::MouseButtonPressed){
					music->stop();
                    return false;
                }
            }else{
				containQuitter = false;
            }
		}
		window.clear();
		window.draw(bk);
		if (containJouer) {
			window.draw(boutonJC);
		}
		else {
			window.draw(boutonJ);
		}
		if (containQuitter) {
			window.draw(boutonQC);
		}
		else {
			window.draw(boutonQ);
		}
		window.display();
	}
}
