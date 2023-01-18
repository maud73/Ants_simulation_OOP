#include "Termite.hpp"
#include "../Application.hpp"

Termite::Termite(ToricPosition tp)
    :Animal(tp, getAppConfig().termite_hp, getAppConfig().termite_lifespan)
{

    Environment* environment = &getAppEnv();
    //Nécéssaire pour le enemyTest
    if(environment != nullptr) {
        getAppEnv().addCompteur(s::TERMITES,1);
    }
}

bool Termite::isFighter() const
{
    return true;
}

double Termite::getSpeed() const
{
    return getAppConfig().termite_speed;
}

sf::Texture& Termite::getTexture() const
{
    return getAppTexture(getAppConfig().termite_texture);
}

void Termite::drawOn(sf::RenderTarget& target) const
{
    sf::Sprite antSprite = buildSprite (getPosition().toVec2d(), 30, getTexture());
    antSprite.setRotation(getDirection()/DEG_TO_RAD);
    target.draw(antSprite);
    if(isDebugOn()) {
        Animal::debugDraw(target);
    }
}

bool Termite::isEnemy (Animal const* entity) const
{
    return entity->isEnemyDispatch(this);
}

bool Termite::isEnemyDispatch (Termite const*) const
{
    return false;
}

bool Termite::isEnemyDispatch (Ant const*) const
{
    return true;
}

int Termite::getStrength() const
{
    return getAppConfig().termite_strength;
}

sf::Time Termite::getAttackDelay() const
{
    return sf::seconds(getAppConfig().termite_attack_delay);
}

Termite::~Termite()
{
    Environment* environment = &getAppEnv();
    //Nécéssaire pour le enemyTest
    if(environment != nullptr) {
        getAppEnv().addCompteur(s::TERMITES,-1);
    }

}
