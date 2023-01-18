/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#pragma once
#ifndef FOOD_HPP
#define FOOD_HPP
#include "Positionable.hpp"
#include "../Utility/Types.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"


class Food:public Positionable, public Drawable
{
private:
    Quantity quantite;
public:
    //constructeur
    Food (ToricPosition tp, Quantity q);

    //méthode

    /*!
     * @brief Enlève une quantité q à la source
     *
     * @param quantité à enlever
     * @return quantité qui a pu être enlevée
     */
    Quantity takeQuantity(Quantity q);

    /*!
     * @brief Dessin de la source de nourriture
     */
    void drawOn(sf::RenderTarget& target) const;

    bool isEmpty() const;

    //destructeur
    virtual ~Food () {};
};

#endif // FOOD_HPP
