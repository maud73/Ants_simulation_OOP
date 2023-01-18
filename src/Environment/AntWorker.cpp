/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "AntWorker.hpp"
#include "../Application.hpp"

//constructeur
AntWorker::AntWorker(ToricPosition tp, Uid f)
    :  Ant (tp, f, getAppConfig().ant_worker_hp, getAppConfig().ant_worker_lifespan), stock(0)
{
    Environment* environment = &getAppEnv();
    //Nécéssaire pour le enemyTest
    if(environment != nullptr) {
        getAppEnv().addCompteur(s::WORKER_ANTS,1);
    }
}

//méthodes
sf::Texture& AntWorker::getTexture() const
{
    return getAppTexture(getAppConfig().ant_worker_texture);
}

void AntWorker::update(sf::Time dt)
{
    Ant::update(dt);
    if (stock <= 0) {
        //Cherche source de nourriture perceptible, si elle existe elle la récupère
        Food* closeFood = getAppEnv().getClosestFoodForAnt(getPosition());
        if (closeFood != nullptr) {
            //Prélèvement de nourriture
            stock+= closeFood->takeQuantity(getAppConfig().ant_max_food);
            antUturn();
        }
    } else {
        Anthill* closeAnthill = getAppEnv().getAnthillForAnt(getPosition(), getAntUid());
        if (closeAnthill != nullptr) {
            //Dépose de nourriture
            closeAnthill->ajoutStock(stock);
            stock = 0;
        }
    }
}

void AntWorker::debugDraw(sf::RenderTarget& target) const
{
    Ant::debugDraw(target);
    auto const text = buildText("stock : "+to_nice_string(stock), getPosition().toVec2d()+Vec2d(20,-10), getAppFont(), 20, sf::Color::Green);
    target.draw(text);
}

bool AntWorker::isFighter() const
{
    return false;
}


int AntWorker::getStrength() const
{
    return getAppConfig().ant_worker_strength;
}

AntWorker::~AntWorker()
{
    Environment* environment = &getAppEnv();
    //Nécéssaire pour le enemyTest
    if(environment != nullptr) {
        getAppEnv().addCompteur(s::WORKER_ANTS,-1);
    }
}
