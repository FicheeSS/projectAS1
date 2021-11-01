#include "entite.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>

Entite::Entite()
{
    float _x=0;
    float _y=0;
    float _xDep=0;
    float _yDep=0;
}

void Entite::update(bool up, bool down, bool left, bool right)
{
    if(up && !down)
    {
        _yDep=1;
    }
    else if (down && !up)
    {
        _yDep=-1;
    }
    else
    {
        _yDep=0;
    }
    if(left && !right)
    {
        _xDep=-1;
    }
    else if(right && !left)
    {
        _xDep=1;
    }
    else
    {
        _xDep=0;
    }

    _x+=_xDep;
    _y+=_yDep;
}

float Entite::getX()const
{
    return _x;
}
float Entite::getY()const
{
    return _y;
}
float Entite::getXDep()const
{
    return _xDep;
}
float Entite::getYDep()const
{
    return _yDep;
}


















