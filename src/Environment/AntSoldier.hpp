/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#ifndef ANTSOLDIER_HPP
#define ANTSOLDIER_HPP
#pragma once
#include "Ant.hpp"


class AntSoldier : public Ant
{
public:
    //constructeur
    AntSoldier(ToricPosition tp, Uid f);
    virtual int getStrength() const override;
    virtual bool isFighter() const override;
    //destructeur
    virtual ~AntSoldier ();




protected:
    //méthodes
    sf::Texture& getTexture() const override;

};

#endif // ANTSOLDIER_HPP
