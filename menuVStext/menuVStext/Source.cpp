#include<iostream>
#include<SFML/Graphics.hpp>
#include"Menu.h"

int main() {

	Menu a;
	if(a.menu()){
        std::cout<<"jeu lance"<<std::endl;
	}else{
        std::cout<<"jeu ferme"<<std::endl;
    }
	return 0;
}
