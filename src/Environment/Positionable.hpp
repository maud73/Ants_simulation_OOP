/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */


#pragma once
#include "ToricPosition.hpp"
#include <ostream>


/*!
 * @brief Manage a position in a toric world
 *
 *
 */
class Positionable
{
private:
    ToricPosition position;

public:
    //constructeurs
    Positionable() = default;
    Positionable(ToricPosition const&);
    //méthodes

    /*!
     * @brief obtenir la position toric
     *
     * @return la position sous la forme d'un ToricPosition
     */
    ToricPosition getPosition () const;

    /*!
     * @brief modifier la position
     *
     * @param position qui remplace celle de l'instance sur laquelle on agit
     */
    void setPosition (const ToricPosition& position);

    /*!
     * @brief affiche les mêmes informations que l'opérateur de sortie <<
     *
     * @param
     * @return
     */
    std::ostream& display (std::ostream& out) const;
    //destructeur
    virtual ~Positionable() {};

};

//surcharges externes
std::ostream& operator<< (std::ostream&, Positionable const&);



