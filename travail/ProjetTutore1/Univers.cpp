#include "Univers.h"

void Univers::animate()
{
    sf::Clock clock;
    float lastTime = 0;
    sf::Font font;
    font.loadFromFile("DS-DIGI.TTF");
    auto currentMusic = RP->getLevelMusic(lvl - 1);
    currentMusic->play();
    currentMusic->setLoop(true);
    while (RW->isOpen()) {
        RW->clear();
        sf::Event event;
        while (RW->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: [[unlikely]];
                RW->close();
                break;
            }
        if (event.type == sf::Event::KeyPressed) {
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
        }

        else if (event.type == sf::Event::KeyReleased) {
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
        /*
        sf::RectangleShape Bound(sf::Vector2f(0, 0));
        Bound.setSize(sf::Vector2f(ter->getSizeofX() * BLOCKWIDTH, ter->getSizeofY() * BLOCKHEIGHT));
        Bound.setPosition(0, 0);
        RW->draw(Bound);
        */
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
        bool listCollision[4] = { isCollidingWithGround (ter,p),isCollidingWithHead(ter,p),isCollidingWithSideRight(ter,p),isCollidingWithSideLeft(ter,p) };
        p->setCollide(listCollision);
        p->show(*RW);
        RW->display();
    }
}
bool isCollidingWithGround(Terrain* t, Player *p)
{
    sf::IntRect rec = p->getRect();
    int x = ceil(rec.left / BLOCKWIDTH);
    int y = ceil(rec.top / BLOCKHEIGHT);
    TerrainElement* tE = nullptr;
    int maxY = t->getSizeofY();
    if (y < t->getSizeofY() -1 ) {
        y++;
    }
    try {
        tE = t->getElementAtPos(x, y); 
    }
    catch (std::out_of_range e) {
        std::cerr << e.what() << " at values "<< x <<" , "<< y  << std::endl;
        return false;
    }
    if (tE->getType() == TerrainElement::Element) {
        return true;
       }
    return false;

}
bool isCollidingWithHead(Terrain* t, Player *p)
{
    sf::IntRect rec = p->getRect();
    int x = ceil(rec.left / BLOCKWIDTH);
    int y = ceil(rec.top / BLOCKHEIGHT);
    TerrainElement* tE = nullptr;
    int maxY = t->getSizeofY();
    try {
        tE = t->getElementAtPos(x, y); 
    }
    catch (std::out_of_range e) {
        std::cerr << e.what() << " at values "<< x <<" , "<< y  << std::endl;
        return false;
    }
    if (tE->getType() == TerrainElement::Element) {
        return true;
       }
    return false;

}
bool isCollidingWithSideRight(Terrain* t, Player *p)
{
    sf::IntRect rec = p->getRect();
    int x = ceil(rec.left / BLOCKWIDTH);
    int y = ceil(rec.top / BLOCKHEIGHT);
    TerrainElement* tE = nullptr;
    int maxY = t->getSizeofY();
    if (x < t->getSizeofX() -1 )  {
        x++;
    }
    try {
        tE = t->getElementAtPos(x, y); 
    }
    catch (std::out_of_range e) {
        std::cerr << e.what() << " at values "<< x <<" , "<< y  << std::endl;
        return false;
    }
    if (tE->getType() == TerrainElement::Element) {
        return true;
       }
    return false;

}
bool isCollidingWithSideLeft(Terrain* t, Player *p)
{
    sf::IntRect rec = p->getRect();
    int x = ceil(rec.left / BLOCKWIDTH);
    int y = ceil(rec.top / BLOCKHEIGHT);
    TerrainElement* tE = nullptr;
    int maxY = t->getSizeofY();
    try {
        tE = t->getElementAtPos(x, y); 
    }
    catch (std::out_of_range e) {
        std::cerr << e.what() << " at values "<< x <<" , "<< y  << std::endl;
        return false;
    }
    if (tE->getType() == TerrainElement::Element) {
        return true;
       }
    return false;

}

Univers::Univers(RessourcePack *rp, sf::RenderWindow* rw)
{   
    RW = rw;
    RP = rp;
    try {
        RP->generateImg("\\Ressources\\img");
        RP->generateAudioData("\\Ressources\\audio");
    }
    catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
        return;
    }
    ter = new Terrain(RP);
    ter->loadTerrain(1);
    terrain = ter->getTerrain();
    p = ter->getPlayer();
    p->setTerrainBoundaries(ter->getSizeofX() * BLOCKWIDTH, ter->getSizeofY()* BLOCKHEIGHT);
}