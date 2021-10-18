#include "RessourcePack.h"


    
void RessourcePack::generateImg(std::string path)
{
    //Rechercher et charger les images dans le HEAP
    std::vector< boost::filesystem::path> paths;
    boost::filesystem::path full_path(boost::filesystem::current_path());
    std::cout << "Current path is : " << full_path << std::endl;
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
    if (paths.empty()) throw std::invalid_argument("Aucune image n'été trouve");
    imgLoc = new std::vector<sf::Image>(paths.size());
    for ( boost::filesystem::path path : paths) {
        sf::Image img;
        if (!img.loadFromFile(path.string())) throw std::invalid_argument("File " + path.string() + "not found"); // on lance une exeption si on n'arrive pas a charger l'image
        imgLoc->push_back(img); // On charge l'image dans le tableau d'image
    }
}

sf::Image RessourcePack::getImg(int n) {
    return imgLoc->at(n);//UHMMM
};

RessourcePack::~RessourcePack() {
    delete(imgLoc);
}