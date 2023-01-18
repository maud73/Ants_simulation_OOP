/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "Pheromone.hpp"
#include "Utility/Utility.hpp"
#include "Application.hpp"

//constructeur
Pheromone::Pheromone(ToricPosition tp, Quantity q)
    : Positionable(tp), quantite(q) {}

//méthode
bool Pheromone::isNegligible () const
{
    if (quantite<getAppConfig().pheromone_threshold) {
        return true;
    } else {
        return false;
    }
}

void Pheromone::drawOn(sf::RenderTarget& target) const //a optimiser
{
    sf::Color couleur(sf::Color::Green);
    couleur.a /=4;
    auto const pheromoneSprite =  buildCircle(getPosition().toVec2d(), 5, couleur);
    target.draw(pheromoneSprite);
}

void Pheromone::update(sf::Time dt)
{
    quantite-=dt.asSeconds()*getAppConfig().pheromone_evaporation_rate;
}

Quantity Pheromone::getQuantity() const
{
    return quantite;
}

