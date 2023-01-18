/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */


#ifndef PHEROMONE_HPP
#define PHEROMONE_HPP
#pragma once
#include "Positionable.hpp"
#include "../Interface/Updatable.hpp"
#include "../Interface/Drawable.hpp"
#include "Utility/Types.hpp"


class Pheromone : public Positionable, public Drawable, public Updatable
{
public:
    //constructeur
    Pheromone(ToricPosition tp, Quantity q);
    //méthode
    bool isNegligible () const;
    void drawOn(sf::RenderTarget& target) const override;
    void update(sf::Time dt) override;
    Quantity getQuantity() const;
    //destructeur
    virtual ~Pheromone() {};

private:
    //attribut
    Quantity quantite;
};

#endif // PHEROMONE_HPP
