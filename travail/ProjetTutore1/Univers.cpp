#include "Univers.h"



void Univers::animate()
{
    sf::Clock clock;
    float lastTime = 0;
    sf::Font font;
    font.loadFromFile("DS-DIGI.TTF");
    auto currentMusic = RP->getLevelMusic(lvl - 1);
    try{
        currentMusic->play();
        currentMusic->setLoop(true);
    }catch(std::exception e){
        currentMusic->stop();
    }
    while (RW->isOpen()) {
        RW->clear();
        sf::Event event;
        while (RW->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: [[unlikely]];
                RW->close();
                currentMusic->stop();
                break;
            }
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
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
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                case sf::Keyboard::Left:
                    dir = std::make_tuple(std::get<0>(dir), DIRDEP::NONE);
                    break;
                case sf::Keyboard::Right:
                    dir = std::make_tuple(std::get<0>(dir), DIRDEP::NONE);
                    break;
                case sf::Keyboard::Up:
                    dir = std::make_tuple(DIRDEP::NONE, std::get<1>(dir));
                    break;
                case sf::Keyboard::Down:
                    dir = std::make_tuple(DIRDEP::NONE, std::get<1>(dir));
                    break;

                }
            }
        }
        for (auto t : *ter->getTerrain()) {
            t->show(RW);
        }
            
        std::vector<bool>* listCollision = collision(p);
        p->move(dir,*listCollision);
        p->show(RW);
        RW->display();
    }
}

std::vector<bool>* Univers::collision(Player* p) {
    for (uint32_t i = 0; i < res->size(); i++) {
        res->at(i) = false;
    }
    for (auto t : *ter->getTerrain()) {

        Block* e = static_cast<Block*>(t);
        if (e->collide(p->getRect())) {
            #ifdef DEBUG
            e->colliding = true;
            #endif // DEBUG
            //On suppose que tous les obj font la même taille
            int xb = e->getX();
            int yb = e->getY();
            int xp = p->getX();
            int yp = p->getY();
             if (yb + BLOCKHEIGHT <= yp + BLOCKHEIGHT / 4 ) {
                res->at(COLDIR::TOP) = true;
             }
            else if (yb >= yp + BLOCKHEIGHT / 4 ) {
                res->at(COLDIR::BOTTOM) = true;
            }
            else if (xp > xb + BLOCKWIDTH/4) {
                res->at(COLDIR::LEFT) = true;
            }
            else if (xp+ BLOCKWIDTH <= xb + BLOCKWIDTH/4 ) {
                res->at(COLDIR::RIGHT) = true;
            }

            else {
                 res->at(COLDIR::TOP) = true;

            }
        }
    }
       // std::printf("Collision BOTTOM : %s, UP : %s ,LEFT : %s , RIGHT %s\n", res->at(COLDIR::BOTTOM) ? "true" : "false", res->at(COLDIR::TOP) ? "true" : "false", res->at(COLDIR::LEFT) ? "true" : "false", res->at(COLDIR::RIGHT) ? "true" : "false");
        return res;
  
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
    p = ter->getPlayer();
    sf::View View(sf::FloatRect(0, 0, ter->getSizeY() * BLOCKWIDTH, ter->getSizeX() * BLOCKHEIGHT));
    std::printf("Current Viewport : %d x %d", ter->getSizeY() * BLOCKWIDTH, ter->getSizeX() * BLOCKHEIGHT);
    rw->setView(View);
    p->setMaxX(ter->getSizeY() * BLOCKWIDTH);
}