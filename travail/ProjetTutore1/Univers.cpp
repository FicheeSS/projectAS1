#include "Univers.h"



void Univers::animate()
{
    sf::Clock clock;
    //float lastTime = 0;
    //sf::Font font;
    //font.loadFromFile("\\Ressources\\DS-DIGI.TTF");
    currentMusic = RP->getLevelMusic(lvl - 1);
    try{
        currentMusic->play();
        currentMusic->setLoop(true);
    }catch(std::exception e){
        currentMusic->stop();
    }
    while (RW->isOpen()) {
        RW->clear();
        if (background != nullptr) {
            RW->draw(*background);
        }
        sf::Event event;
        while (RW->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: [[unlikely]];
                shutdown();
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
        for (auto t : *ter->getTerrain()) {
            t->show(RW);
        }
        #ifdef DEBUG
        if (ctrlIsInUse && tabIsUse) {
            lvl++;
            loadTerrain(lvl);
            if (!RW->isOpen()) {
                return;
            }
            ctrlIsInUse = false;
            tabIsUse = false;
        }
        #endif // DEBUG

        std::vector<bool>* listCollision = collision(p);
        p->move(dir,*listCollision);
        p->show(RW);
        RW->display();
    }
}

std::vector<bool>* Univers::collision(Character* p) {
    for (uint32_t i = 0; i < res->size(); i++) {
        res->at(i) = false;
    }
    for (auto t : *ter->getTerrain()) {

        Block* e = static_cast<Block*>(t);
        if (e->collide(p->getRect())) {
                #ifdef DEBUG
                e->colliding = true;
                #endif // DEBUG
  
                InteractiveObject* it = dynamic_cast<InteractiveObject*>(e);
                if (it != nullptr) {
                    if (it->effectPlayer((Player *)p)) {
                        for (uint32_t i = 0; i < ter->getTerrain()->size();i++) {
                            if (ter->getElementAtPos(i) == it) {
                                ter->getTerrain()->erase(ter->getTerrain()->begin() + i);
                                break;
                            }
                        }
                    }
                    continue;
                }
                int xb = static_cast<int>(e->getX());
                int yb = static_cast<int>(e->getY());
                int xp = static_cast<int>(p->getX());
                int yp = static_cast<int>(p->getY());
                sf::Vector2u size = p->getSize();
                if (yb + size.y <= yp + size.y / 3) {
                    res->at(COLDIR::TOP) = true;
                }
                else if ((unsigned int)yb >= yp + size.y / 4) {
                    res->at(COLDIR::BOTTOM) = true;
                }
                else if ((unsigned int)xp > xb + size.x / 4) {
                    res->at(COLDIR::LEFT) = true;
                }
                else if (xp + size.x <= xb + size.x / 4) {
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

void Univers::loadTerrain(int lvl)
{
    if (ter != nullptr) {
        delete(ter);
    }
    if (currentMusic != nullptr) {
        currentMusic->stop();
        currentMusic = RP->getLevelMusic(lvl - 1);
        currentMusic->setLoop(true);
        currentMusic->play();

    }
    ter = new Terrain(RP);
    try {
        ter->loadTerrain(lvl);
    }
    catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
        shutdown();
        return;
    }
    p = ter->getPlayer();
    if(backgroundTex != nullptr){
        delete(backgroundTex);
    }
    delete(background);
    backgroundTex = new sf::Texture();
    sf::Vector2i si = sf::Vector2i(ter->getSizeY() * BLOCKWIDTH, ter->getSizeX() * BLOCKHEIGHT);
    backgroundTex->setSmooth(true);
    backgroundTex->setRepeated(true);
    backgroundTex->loadFromImage(*RP->getImgBackground(1), sf::IntRect(sf::Vector2i(0,0),si));
    background = new sf::Sprite(*backgroundTex);
    #pragma warning( push ) 
    #pragma warning( disable : 4244)
    sf::View View(sf::FloatRect(0, 0, ter->getSizeY() * BLOCKWIDTH, ter->getSizeX() * BLOCKHEIGHT));
    #pragma warning( pop ) 

    std::printf("Current Viewport : %d x %d", ter->getSizeY() * BLOCKWIDTH, ter->getSizeX() * BLOCKHEIGHT);
    RW->setView(View);
    p->setMaxX(ter->getSizeY() * BLOCKWIDTH);
}

void Univers::shutdown()
{
    RW->close();
    currentMusic->stop();
}


Univers::Univers(RessourcePack *rp, sf::RenderWindow* rw)
{   
    RW = rw;
    RP = rp;

    try {
        RP->generateImg("\\Ressources\\img");
        RP->generateAudioData("\\Ressources\\audio");
        RP->generateBackgrounds("\\Ressources\\img\\backgrounds");
    }
    catch (std::invalid_argument e) {
        std::cerr << e.what() << std::endl;
        shutdown();
        return;
    }
    loadTerrain(1);


}