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

void keyboardInput(bool entiteRight, bool entiteLeft, bool entiteUp, bool entiteDown, Entite& joueur, float vitesse, bool syndromeCoordinationOppose)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        entiteRight=true;
    }
    else
    {
        entiteRight=false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        entiteLeft=true;
    }
    else
    {
        entiteLeft=false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        entiteUp=true;
    }

    else
    {
        entiteUp=false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        entiteDown=true;
    }

    else
    {
        entiteDown=false;
    }

    joueur.update(entiteUp,entiteDown,entiteLeft,entiteRight, vitesse, syndromeCoordinationOppose);
}

void Entite::update(bool up, bool down, bool left, bool right, float vitesse, bool syndromeCoordinationOppose)
{
    if(syndromeCoordinationOppose)
    {
        if(up && !down)
        {
            _yDep=vitesse;
        }
        else if (down && !up)
        {
            _yDep=-vitesse;
        }
        else
        {
            _yDep=0;
        }
        if(left && !right)
        {
            _xDep=-vitesse;
        }
        else if(right && !left)
        {
            _xDep=vitesse;
        }
        else
        {
            _xDep=0;
        }

        _x+=_xDep;
        _y+=_yDep;
    }

    else
    {
        if(up && !down)
        {
            _yDep=-vitesse;
        }
        else if (down && !up)
        {
            _yDep=vitesse;
        }
        else
        {
            _yDep=0;
        }
        if(left && !right)
        {
            _xDep=-vitesse;
        }
        else if(right && !left)
        {
            _xDep=vitesse;
        }
        else
        {
            _xDep=0;
        }

        _x+=_xDep;
        _y+=_yDep;
    }
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











