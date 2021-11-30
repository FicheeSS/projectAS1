#ifndef ENTITE_H_INCLUDED
#define ENTITE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Univers.h"


class Entite
{
    const float VIT_DEP_X = 4; // Vitesse de déplacement de _x
    const float VIT_DEP_MAX_X = 4;
    const float VIT_DEP_Y = 0.75; // Vitesse de déplacement de _y
    const float VIT_DEP_MAX_Y = 20;
    const float DIST_SAUT = 20; // Distance de saut

private:
    float _xDep; // Déplacement actuel de x
    float _yDep; // Déplacement actuel de y
    float _echelleX; // Echelle de X
    float _echelleY; // Echelle de Y
    sf::Sprite _sprite; // Sprite du personnage
    float _limAbsDroit; // Limite droit du personnage
    float _limAbsBase; // Limite base du personnage

    /// Attributs calculés
    bool _orientation; // TRUE = Regarde à droit / FALSE = Regarde à gauche
    bool _saut=false; // Saut TRUE/FALSE
    float _dernContColY; // Dernier valeur de _y quand collitionY=-1
    float _limRelDroit; // Limite droit du personnage
    float _limRelGauche; // Limite gauche du personnage
    float _limRelSommet; // Limite sommet du personnage
    float _limRelBase; // Limite base du personnage
    bool _collisionXG; // Collision à gauche
    bool _collisionXD; // Collision à droit
    bool _collisionYH; // Collision en haut
    bool _collisionYB; // Collision en bas


public :

    Entite(sf::Sprite, float echX=1, float echY=1); // Constructeur

    //void update(bool up, bool down, bool left, bool right, Bloc sol);//, Bloc plat1); // Gravité
    void update(bool up, bool down, bool left, bool right, Bloc sol, Bloc plat1); // Gravité
    void update(bool up, bool down, bool left, bool right, float vitesse, Bloc sol, Bloc plat1); // Pas de gravité
    void update(bool up, bool down, bool left, bool right, float vitesse, const vector <Bloc>&); // Pas de gravité

    void calculDesLimitsRel();
    void collision(const Bloc&);
    void collision2(const Bloc&,const Bloc&);
    void collision(const vector <Bloc>&  plats);


    /// Getters :
    float getXDep()const;
    float getYDep()const;
    float getEchelleX() const;
    float getEchelleY() const;
    sf::Sprite getSprite() ;
    float getLimAbsDroit() const;
    float getLimAbsBase() const;

    bool getOrientation() const;
    bool getSaut() const;
    float getDernContColY() const;
    float getLimRelDroit() const;
    float getLimRelGauche() const;
    float getLimRelSommet() const;
    float getLimRelBase() const;
    bool getCollisionYB() const;
    bool getCollisionYH() const;
    bool getCollisionXG() const;
    bool getCollisionXD() const;


    /// Setters :
    void setXDep(float);
    void setYDep(float);
    void setEchelleX(float);
    void setEchelleY(float);
    void setSprite(sf::Sprite);
    void setLimAbsDroit(float);
    void setLimAbsBase(float);

    void setOrientation(bool);
    void setSaut(bool);
    void setDernContColY(float);
    void setLimRelDroit(float);
    void setLimRelGauche(float);
    void setLimRelSommet(float);
    void setLimRelBase(float);
    void setCollisionYB(bool);
    void setCollisionYH(bool);
    void setCollisionXG(bool);
    void setCollisionXD(bool);
};

#endif // ENTITE_H_INCLUDED
