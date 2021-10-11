#include "RessourcePack.h"


    
void RessourcePack::generateImg(std::string path)
{
    //Rechercher et charger les images dans le HEAP
    std::vector< boost::filesystem::path> paths;

    if ( boost::filesystem::exists(path) &&  boost::filesystem::is_directory(path)) {

        //on cherche tous les fichiers avec EXT dans path
        for (auto const& entry :  boost::filesystem::recursive_directory_iterator(path))
        {
            if ( boost::filesystem::is_regular_file(entry) && entry.path().extension() == EXT) {
                paths.emplace_back(entry.path());
            }
        }
    }
    for ( boost::filesystem::path path : paths) {
        sf::Image img;
        if (!img.loadFromFile(path.string())) throw std::invalid_argument("File " + path.string() + "not found"); // on lance une exeption si on n'arrive pas a charger l'image
        imgLoc->push_back(img); // On charge l'image dans le tableau d'image
        imgList->push_back(&imgLoc->at(imgLoc->size() - 1)); //On liste les pointeurs vers les images du tableau

    }
}

sf::Image* RessourcePack::getImg(int n) {
    return imgList->at(n);
};

RessourcePack::~RessourcePack() {
    delete(imgList);
    delete(imgLoc);
}