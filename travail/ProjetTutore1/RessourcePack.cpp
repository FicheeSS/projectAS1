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
            if ( boost::filesystem::is_regular_file(entry) && entry.path().extension() == IMGEXT) {
                paths.emplace_back(entry.path());
            }
        }
    }
    if (paths.empty()) throw std::invalid_argument("Aucune image n'été trouve");
    for ( boost::filesystem::path path : paths) {
        sf::Image *img = new sf::Image();
        if (!img->loadFromFile(path.string())) throw std::invalid_argument("File " + path.string() + "not found"); // on lance une exeption si on n'arrive pas a charger l'image
        boost::regex nb("[0-9]*");
        if (boost::regex_match(path.stem().string(),nb) ) {
            imgLoc->push_back(img); // On charge l'image dans le tableau d'image
        }
        else {
            if (boost::algorithm::contains(path.string(),"left.png")) {
                imgLocPlayer->at(LEFT)= img;
            }
            else if (boost::algorithm::contains(path.string() , "right.png")) {
                imgLocPlayer->at(RIGHT) = img;

            }
            else if (boost::algorithm::contains(path.string() ,"up.png")) {
                imgLocPlayer->at(UP) = img;
            }
            else  {
                imgLocPlayer->at(DOWN) = img;
            }
        }
    }
}
void RessourcePack::generateAudioData(std::string path)
{
    //Rechercher et charger les images dans le HEAP
    std::vector< boost::filesystem::path> paths;
    boost::filesystem::path full_path(boost::filesystem::current_path());
    //std::cout << "Current path is : " << full_path << std::endl;
    path = full_path.string() + path;

    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {

        //on cherche tous les fichiers avec EXT dans path
        for (auto const& entry : boost::filesystem::recursive_directory_iterator(path))
        {
            if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == AUDEXT) {
                paths.emplace_back(entry.path());
            }
        }
    }
    if (paths.empty()) throw std::invalid_argument("Aucune image n'été trouve");
    for (auto path : paths) {
        std::regex nb(".*\\\d*\.flac");
        if (std::regex_search(path.string(), nb)) {
            sf::Music* music = new sf::Music;
            if (!music->openFromFile(path.string())) throw std::invalid_argument("La musique " + path.string() + " n'a pas été trouvé");
            musicList->push_back(music);
        }
        else {
            sf::SoundBuffer* buffer = new sf::SoundBuffer;
            if (!buffer->loadFromFile(path.string()))throw std::invalid_argument("Le fichier audio " + path.string() + " n'a pas été trouvé");
            soundList->push_back(std::make_tuple(path.stem().string(), buffer));
        }
    }
}

sf::SoundBuffer* RessourcePack::getSoundBufferByName(std::string name)
{
    for (auto select : *soundList) {
        if (std::get<0>(select) == name) {
            return std::get<1>(select);
        }
    }
    return nullptr;
}
RessourcePack::RessourcePack()
{
    imgLoc = new std::vector<sf::Image*>;
    imgLocPlayer = new std::vector<sf::Image*>(4);
    soundList = new std::vector<std::tuple<std::string, sf::SoundBuffer*>>;
    musicList = new std::vector<sf::Music*>;

}

sf::Image* RessourcePack::getImg(int n) {
    return imgLoc->at(n -1);
};

RessourcePack::~RessourcePack() {
    for (uint32_t i = 0; i < imgLoc->size(); i++) {
        delete(imgLoc->at(i));
    }
    for (uint32_t i = 0; i < imgLocPlayer->size(); i++) {
        delete(imgLocPlayer->at(i));
    }
    for (uint32_t i = 0; i < musicList->size(); i++) {
        delete(musicList->at(i));
    }
    for (uint32_t i = 0; i < soundList->size(); i++) {
        delete(std::get<1>(soundList->at(i)));
    }
    delete(soundList);
    delete(musicList);
    delete(imgLocPlayer);
    delete(imgLoc);
}