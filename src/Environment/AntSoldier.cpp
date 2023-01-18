/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "AntSoldier.hpp"
#include "Application.hpp"

//constructeur
AntSoldier::AntSoldier(ToricPosition tp, Uid f)
    : Ant (tp, f, getAppConfig().ant_soldier_hp, getAppConfig().ant_soldier_lifespan)
{
    //Nécéssaire pour le enemyTest
    Environment* environment = &getAppEnv();
    if(environment != nullptr) {
        getAppEnv().addCompteur(s::SOLDIER_ANTS,1);
    }
}

//méthodes
sf::Texture& AntSoldier::getTexture() const
{
    return getAppTexture(getAppConfig().ant_soldier_texture);
}

bool AntSoldier::isFighter() const
{
    return true;
}

int AntSoldier::getStrength() const
{
    return getAppConfig().ant_soldier_strength;
}

//destructeur
AntSoldier::~AntSoldier ()
{
    //Nécéssaire pour le enemyTest
    Environment* environment = &getAppEnv();
    if(environment != nullptr) {
        getAppEnv().addCompteur(s::SOLDIER_ANTS,-1);
    }
}
