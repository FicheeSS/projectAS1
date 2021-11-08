#include "RessourcePack.h"


    
void RessourcePack::generateImg(std::string path)
{
    //Rechercher et charger les images dans le HEAP
    std::vector< boost::filesystem::path> paths;
    boost::filesystem::path full_path(boost::filesystem::current_path());
    //std::cout << "Current path is : " << full_path << std::endl;
    path =   full_path.string() + path;

    if ( boost::filesystem::exists(path) &&  boost::filesystem::is_directory(path)) {

        //on cherche tous les fichiers avec EXT dans path
        for (auto const& entry :  boost::filesystem::recursive_directory_iterator(path))
        {
            if ( boost::filesystem::is_regular_file(entry) && entry.path().extension() == EXT) {
                paths.emplace_back(entry.path());
            }
        }
    }
    if (paths.empty()) throw std::invalid_argument("Aucune image n'�t� trouve");
    imgLoc = new std::vector<sf::Image*>;
    for ( boost::filesystem::path path : paths) {
        sf::Image *img = new sf::Image();
        if (!img->loadFromFile(path.string())) throw std::invalid_argument("File " + path.string() + "not found"); // on lance une exeption si on n'arrive pas a charger l'image
        std::regex nb(".*([0-9])*.png");
        if (std::regex_match(path.string(),nb) ) {
            imgLoc->push_back(img); // On charge l'image dans le tableau d'image
        }
        else {
            if (path.string() == "left.png") {
                imgLocPlayer->at(LEFT)= img;
            }
            else if (path.string() == "right.png") {
                imgLocPlayer->at(RIGHT) = img;

            }
            else if (path.string() == "up.png") {
                imgLocPlayer->at(UP) = img;
            }
            else  {
                imgLocPlayer->at(DOWN) = img;
            }
        }
    }
}

RessourcePack::RessourcePack()
{
    imgLoc = nullptr;
    imgLoc = new std::vector<sf::Image*>(4);
}

sf::Image* RessourcePack::getImg(int n) {
    return imgLoc->at(n);
};

RessourcePack::~RessourcePack() {
    for (uint32_t i = 0; i < imgLoc->size(); i++) {
        delete(imgLoc->at(i));
    }
    delete(imgLoc);
}