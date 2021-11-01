#ifndef ENTITE_H_INCLUDED
#define ENTITE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>


class Entite
{
private:
    float _x=0;
    float _y=0;
    float _xDep =0;
    float _yDep =0;

public :
    Entite();

    void update(bool up, bool down, bool left, bool right);

    float getX()const;
    float getY()const;
    float getXDep()const;
    float getYDep()const;

};

#endif // ENTITE_H_INCLUDED
