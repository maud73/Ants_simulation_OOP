/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "Positionable.hpp"


//constructeurs
Positionable::Positionable(ToricPosition const& tp)
    : position(tp) {}
//méthodes
ToricPosition Positionable::getPosition () const
{
    return position;
}

void Positionable::setPosition (const ToricPosition& tp)
{
    position = tp;
}

std::ostream& Positionable::display (std::ostream& out) const
{
    out << position;
    return out;
}

//surcharges externes
std::ostream& operator<< (std::ostream& out, Positionable const& p)
{
    p.display(out);
    return out;
}
