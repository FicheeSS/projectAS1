#include "Entite.h"
#include "Univers.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>


///-----------------------------------------------------------------------------------------------------------------------------
/// Constructeurs
///-----------------------------------------------------------------------------------------------------------------------------
Entite::Entite(sf::Sprite sprite, float echX, float echY)
{
    _xDep=0;
    _yDep=0;
    _echelleX=echX;
    _echelleY=echY;
    _sprite = sprite;
    _orientation=true;

    _sprite.setScale(echX,echY);

    _limAbsDroit=_sprite.getLocalBounds().width*_echelleX;
    _limAbsBase=_sprite.getLocalBounds().height*_echelleY;;
}


///-----------------------------------------------------------------------------------------------------------------------------
/// Update de movement
///-----------------------------------------------------------------------------------------------------------------------------

void Entite::update(bool up, bool down, bool left, bool right, float vitesse,/*const vector <Bloc>& vBloc,*/Bloc sol,Bloc plat1)
{
    if(up && !down && !_collisionYH)
    {
        _yDep=-vitesse;
    }
    else if (down && !up && !_collisionYB)
    {
        _yDep=vitesse;
    }
    else
    {
        _yDep=0;
    }
    if(left && !right && !_collisionXD)
    {
        _xDep=-vitesse;
    }
    else if(right && !left && !_collisionXG)
    {
        _xDep=vitesse;
    }
    else
    {
        _xDep=0;
    }
/*
    if(_collisionYB)
    {
        _yDep=0;
    }
*/
    _sprite.move(_xDep,_yDep);
    calculDesLimitsRel();
    collision2(sol,plat1);
//    collision(vBloc);
}



///-----------------------------------------------------------------------------------------------------------------------------
void Entite::update(bool up, bool down, bool left, bool right, Bloc sol, Bloc plat1)
{
    /// Calcul sens de movement axe Y :

    if(_collisionYB && !up) /// Si en terre et pas de saut
    {
        _dernContColY= _sprite.getPosition().y;
        _yDep=0;
    }

    else if(!_collisionYB && !_saut) /// Si pas en terre et pas de saut
    {
        if(_yDep<VIT_DEP_MAX_Y) _yDep+=VIT_DEP_Y;
        else
        {
            _yDep=VIT_DEP_MAX_Y;
        }
    }

    else if (up && !down) /// Si sur terre et saute
    {
        if(!_collisionYH)
        {
            _saut=true;
            if(_yDep>-VIT_DEP_MAX_Y) _yDep+=-VIT_DEP_MAX_Y;
            else if(_yDep==-VIT_DEP_MAX_Y) _yDep=-VIT_DEP_MAX_Y+VIT_DEP_Y;
        }
        else
        {
            _saut=false;
            _yDep=0;
        }
    }

    /*
    else if (down && !up)
    {

    }
    */


    /// Calcul sens de movement axe X :
    if(left && !right && !_collisionXD)
    {
        _xDep=-VIT_DEP_X;
        _orientation=false;
    }

    else if(right && !left && !_collisionXG)
    {
        _xDep=VIT_DEP_X;
        _orientation=true;
    }
    else
    {
        _xDep=0;
    }


    /// Calcul fin de saut

    if ( (_saut && _sprite.getPosition().y<=(_dernContColY-DIST_SAUT) ) || _collisionYH) // Hauteur maximale du saut atteint -> fin de saut
    {
        _saut=false;
    }


    /// Application de la vitesse sur le movement

    _sprite.move(_xDep,_yDep);
    calculDesLimitsRel();
//    collision(sol);
    collision2(sol,plat1);
}



///-----------------------------------------------------------------------------------------------------------------------------
/// CalculDesLimitsRel
///-----------------------------------------------------------------------------------------------------------------------------

void Entite::calculDesLimitsRel()
{
    _limRelGauche = _sprite.getPosition().x;
    _limRelSommet = _sprite.getPosition().y;
    _limRelDroit = _sprite.getPosition().x + (_limAbsDroit);
    _limRelBase = _sprite.getPosition().y + (_limAbsBase);

    //std::cout << " Bas : " << _limRelBase << "  / Haut : " << _limRelSommet << "  / Gauche : " << _limRelGauche << "  / Droit : " << _limRelDroit << std::endl;
}



///-----------------------------------------------------------------------------------------------------------------------------
/// Collisions
///-----------------------------------------------------------------------------------------------------------------------------

void Entite::collision(const Bloc& plateforme)
{
    bool collision;

    collision=_sprite.getGlobalBounds().intersects(plateforme.getSprite().getGlobalBounds());

    _collisionYB=(collision && _limRelBase<plateforme.getCoteBase());
    _collisionYH=(collision && _limRelSommet>plateforme.getCoteSommet());

    _collisionXG=(collision && _limRelGauche<plateforme.getCoteGauche());
    _collisionXD=(collision && _limRelDroit>plateforme.getCoteDroit());


    std::cout << "_collisionYB : " <<_collisionYB  <<  "  / _collisionYH : " <<_collisionYH  <<  "  / _collisionXG : " <<_collisionXG  <<  "  / _collisionXD : " <<_collisionXD  << std::endl;
}



///-----------------------------------------------------------------------------------------------------------------------------

void Entite::collision(const vector <Bloc>& plats)
{
    if(plats.size()<1) throw invalid_argument ("ERROR : table de plateformes vide");

    int i=0;
    bool collision, b,h,g,d;
    do
    {
        collision=_sprite.getGlobalBounds().intersects(plats[i].getSprite().getGlobalBounds());
        i++;
    }while(!collision || i< plats.size());

    i=0;
    do
    {
        b=(collision && _limRelBase<plats[i].getCoteBase());
        i++;
    }while((!(b) || i<plats.size()));

    i=0;
    do
    {
        h=(collision && _limRelSommet>plats[i].getCoteSommet());
        i++;
    }while((!(h) || i<plats.size()));

    i=0;
    do
    {
        g=(collision && _limRelGauche<plats[i].getCoteGauche());
        i++;
    }while((!(g) || i<plats.size()));

    i=0;
    do
    {
        d=(collision && _limRelDroit>plats[i].getCoteDroit());
        i++;
    }while((!(d) || i<plats.size()));

    _collisionYB=b;
    _collisionYH=h;
    _collisionXG=g;
    _collisionXD=d;
}



///-----------------------------------------------------------------------------------------------------------------------------

void Entite::collision2(const Bloc& plateforme, const Bloc& plateforme2)
{
    bool collision, collision2,
    d, g, h, b,
    d2, g2, h2, b2 ;

    collision=_sprite.getGlobalBounds().intersects(plateforme.getSprite().getGlobalBounds());

    b=(collision && _limRelBase<plateforme.getCoteBase());
    h=(collision && _limRelSommet>plateforme.getCoteSommet());

    g=(collision && _limRelGauche<plateforme.getCoteGauche());
    d=(collision && _limRelDroit>plateforme.getCoteDroit());


    collision2=_sprite.getGlobalBounds().intersects(plateforme2.getSprite().getGlobalBounds());

    b2=(collision2 && _limRelBase<plateforme2.getCoteBase());
    h2=(collision2 && _limRelSommet>plateforme2.getCoteSommet());

    g2=(collision2 && _limRelGauche<plateforme2.getCoteGauche());
    d2=(collision2 && _limRelDroit>plateforme2.getCoteDroit());

    _collisionYB=(b||b2);
    _collisionYH=(h||h2);
    _collisionXG=(g||g2);
    _collisionXD=(d||d2);

    std::cout << "_collisionYB : " <<_collisionYB  <<  "  / _collisionYH : " <<_collisionYH  <<  "  / _collisionXG : " <<_collisionXG  <<  "  / _collisionXD : " <<_collisionXD
    <<" b"<<b<<b2<<" h"<<h<<h2<<" g"<<g<<g2<<" d"<<d<<d2 << std::endl;
}



///-----------------------------------------------------------------------------------------------------------------------------
/// Getters :
///-----------------------------------------------------------------------------------------------------------------------------

float Entite::getXDep() const
{
    return _xDep;
}

float Entite::getYDep() const
{
    return _yDep;
}

float Entite::getEchelleX() const
{
    return _echelleX;
}

float Entite::getEchelleY() const
{
    return _echelleY;
}

sf::Sprite Entite::getSprite()
{
    return _sprite;
}

float Entite::getLimAbsDroit() const
{
    return _limAbsDroit ;
}

float Entite::getLimAbsBase() const
{
    return _limAbsBase ;
}

bool Entite::getOrientation() const
{
    return _orientation;
}

bool Entite::getSaut() const
{
    return _saut;
}

float Entite::getDernContColY() const
{
    return _dernContColY;
}

float Entite::getLimRelDroit() const
{
    return _limRelDroit ;
}

float Entite::getLimRelGauche() const
{
    return _limRelGauche ;
}

float Entite::getLimRelSommet() const
{
    return _limRelSommet ;
}

float Entite::getLimRelBase() const
{
    return _limRelBase ;
}

bool Entite::getCollisionYB() const
{
    return _collisionYB;
}

bool Entite::getCollisionYH() const
{
    return _collisionYH;
}

bool Entite::getCollisionXG() const
{
    return _collisionXG;
}

bool Entite::getCollisionXD() const
{
    return _collisionXD;
}




///-----------------------------------------------------------------------------------------------------------------------------
/// Setters :
///-----------------------------------------------------------------------------------------------------------------------------

void Entite::setXDep(float x)
{
    _xDep=x;
}

void Entite::setYDep(float y)
{
    _yDep=y;
}

void Entite::setEchelleX(float x)
{
    _echelleX=x;
}

void Entite::setEchelleY(float y)
{
    _echelleY=y;
}

void Entite::setSprite(sf::Sprite sprite)
{
    _sprite=sprite;
}

void Entite::setLimAbsDroit(float x)
{
    _limAbsDroit=x;
}

void Entite::setLimAbsBase(float x)
{
    _limAbsBase=x;
}

void Entite::setOrientation(bool ori)
{
    _orientation=ori;
}

void Entite::setSaut(bool s)
{
    _saut=s;
}

void Entite::setDernContColY(float y)
{
    _dernContColY=y;
}

void Entite::setLimRelDroit(float x)
{
    _limRelDroit=x;
}

void Entite::setLimRelGauche(float x)
{
    _limRelGauche=x;
}

void Entite::setLimRelSommet(float y)
{
    _limRelSommet=y;
}

void Entite::setLimRelBase(float y)
{
    _limRelBase=y;
}

void Entite::setCollisionYB(bool col)
{
    _collisionYB=col;
}

void Entite::setCollisionYH(bool col)
{
    _collisionYH=col;
}

void Entite::setCollisionXG(bool col)
{
    _collisionXG=col;
}

void Entite::setCollisionXD(bool col)
{
    _collisionXD=col;
}




