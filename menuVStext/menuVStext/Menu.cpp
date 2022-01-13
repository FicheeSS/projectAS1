#include "Menu.h"

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}

bool Menu::menu(){

    //icon pour la barre des taches (logo du jeu)
	sf::Image icon;
	if(!icon.loadFromFile("img.png"))
        std::cout<<"erreur icon"<<std::endl;
	
	//window deplacable mais non redimensionnable 
	sf::RenderWindow window(sf::VideoMode(1200, 700), "Menu",sf::Style::Titlebar);
	window.setIcon(256,256,icon.getPixelsPtr());

	//load des textures a partir des images
	//background
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile("BK2.png")) {
		return EXIT_FAILURE;
	}
	//bouton jouer
	sf::Texture* boutonjouer = new sf::Texture();
	if (!boutonjouer->loadFromFile("boutonjouer.png")) {
		return EXIT_FAILURE;
	}
	//bouton jouer quand la souris passe dessus
	sf::Texture* boutonjouerclick = new sf::Texture();
	if (!boutonjouerclick->loadFromFile("boutonjouerclick.png")) {
		return EXIT_FAILURE;
	}
	//bouton quitter
	sf::Texture* boutonquitter = new sf::Texture();
	if (!boutonquitter->loadFromFile("boutonquitter.png")) {
		return EXIT_FAILURE;
	}
	//bouton quitter qd la souris passe dessus
	sf::Texture* boutonquitterclick = new sf::Texture();
	if (!boutonquitterclick->loadFromFile("boutonquitterclick.png")) {
		return EXIT_FAILURE;
	}

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
		sf::Event event;
		while (window.pollEvent(event)) {
			//si on press escape alors on ferme le jeu
			if (event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			//si la souris est sur le bouton jouer
            if (jbound.contains((sf::Vector2f)sf::Mouse::getPosition(window))) {
				containJouer = true; // pour afficher le bon bouton dans le draw plus loin
				//si il click
				if(event.type == sf::Event::MouseButtonPressed){
                    return true;
                }
            }else {
				containJouer = false;
            }
			//si il est sur le bouton quitter
            if(qbound.contains((sf::Vector2f)sf::Mouse::getPosition(window))){
				containQuitter = true;
                if(event.type == sf::Event::MouseButtonPressed){
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
