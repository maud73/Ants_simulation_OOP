/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "Food.hpp"
#include <Application.hpp>

//constructeur
Food::Food (ToricPosition tp, Quantity q)
    :Positionable(tp), quantite(q) {}

//méthode
Quantity Food::takeQuantity(Quantity q)
{
    if(quantite>=q) {
        quantite-=q;
    } else {
        q=quantite;
        quantite=0;
    }
    return q;
}

void Food::drawOn(sf::RenderTarget& target) const
{
    auto const foodSprite = buildSprite(getPosition().toVec2d(), quantite/2, getAppTexture(getAppConfig().food_texture));
    target.draw(foodSprite);
    if(isDebugOn()) {
        auto const text = buildText(to_nice_string(quantite), getPosition().toVec2d(), getAppFont(), 15, sf::Color::Black);
        target.draw(text);
    }
}

bool Food::isEmpty() const
{
    if(quantite<=0) {
        return true;
    } else {
        return false;
    }
}
