#include "Univers.h"

void Univers::animate()
{
    while (RW->isOpen()) {
        RW->clear();
        sf::Event event;
        while (RW->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: [[unlikely]];
                RW->close();
                break;
            case sf::Event::MouseMoved:
                ////std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                ////std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    dir = std::make_tuple(std::get<0>(dir), Player::LEFT);
                    break;
                case sf::Keyboard::Right:
                    dir = std::make_tuple(std::get<0>(dir), Player::RIGHT);
                    break;
                case sf::Keyboard::Up:
                    dir = std::make_tuple(Player::UP, std::get<1>(dir));
                    break;
                case sf::Keyboard::Down:
                    dir = std::make_tuple(Player::DOWN, std::get<1>(dir));
                    break;
                }
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    dir = std::make_tuple(std::get<0>(dir), Player::NONE);
                    break;
                case sf::Keyboard::Right:
                    dir = std::make_tuple(std::get<0>(dir), Player::NONE);
                    break;
                case sf::Keyboard::Up:
                    dir = std::make_tuple(Player::NONE, std::get<1>(dir));
                    break;
                case sf::Keyboard::Down:
                    dir = std::make_tuple(Player::NONE, std::get<1>(dir));
                    break;

                }

            }
        }
        p->move(dir);
        for (auto ligne : *terrain) {
            for (TerrainElement* t : *ligne) {
                switch (t->getType()) {
                case TerrainElement::Tile:
                    break;
                case TerrainElement::Element:
                    Block* e = static_cast<Block*>(t);
                    e->show(*RW);
                    break;

                }
            }
        }
        p->show(*RW);
        RW->display();
    }
}
Univers::Univers(RessourcePack *rp, sf::RenderWindow* rw)
{   
    RW = rw;
    RP = rp;
    try {
        RP->generateImg("\\Ressources\\img");
    }
    catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    t = new Terrain(RP);
    t->loadTerrain(1);
    terrain = t->getTerrain();
    p = t->getPlayer();
}