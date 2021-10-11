#include "RessourcePack.h"
RessourcePack::RessourcePack(std::string path) {
	//Rechercher et charger les images dans le HEAP
    std::vector<fs::path> paths;

    if (fs::exists(path) && fs::is_directory(path)){
    
        //on cherche tous les fichiers avec EXT dans path
        for (auto const& entry : fs::recursive_directory_iterator(path))
        {
            if (fs::is_regular_file(entry) && entry.path().extension() == EXT)
                paths.emplace_back(entry.path().filename()); 
        }
    }
    for (fs::path path : paths) {
        sf::Image img;
        if (!img.loadFromFile(path.string())) throw std::invalid_argument("File " + path.string() + "not found"); // on lance une exeption si on n'arrive pas a charger l'image
        imgLoc.push_back(img); // On charge l'image dans le tableau d'image
        imgList.push_back(&imgLoc[imgLoc.size()-1]); //On liste les 

    }
}

std::vector<sf::Image*> RessourcePack::getImgList() {
	return imgList;
}

RessourcePack::~RessourcePack() {
	imgLoc.~vector();
	imgList.~vector();
}