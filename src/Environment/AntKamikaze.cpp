#include "AntKamikaze.hpp"
#include "Application.hpp"


AntKamikaze::AntKamikaze(ToricPosition tp, Uid f, Angle direction, double distance)
    : Ant(tp, f, getAppConfig().ant_kamikaze_hp, getAppConfig().ant_kamikaze_lifespan)
{
    setDirection(direction);
    decompteExplosion = sf::seconds (distance/getSpeed());
    getAppEnv().addCompteur(s::KAMIKAZE_ANTS,1);
}


//methodes
int AntKamikaze::getStrength() const
{
    return getAppConfig().ant_kamikaze_strength;
}

void AntKamikaze::update(sf::Time dt)
{
    Ant::update(dt);
    if (decompteExplosion <= sf::Time::Zero) {
        /* Explosion : Environment::antKamikazeExplosion(ToricPosition explosion)
         * toute Anthill dans getAppConfig().ant_kamikaze_explosionradius diparait
         * les animaux perdent getAppConfig().ant_kamikaze_explosionimpact
        */
        getAppEnv().antKamikazeExplosion(getPosition());
    } else {
        decompteExplosion -= dt;
    }


}

sf::Texture& AntKamikaze::getTexture() const
{
    return getAppTexture(getAppConfig().ant_kamikaze_texture);
}
void AntKamikaze::move(sf::Time dt)
{
    Vec2d vecteur_direction_normalise = Vec2d::fromAngle(getDirection()).normalised();
    Vec2d vecteur_vitesse (getSpeed()*vecteur_direction_normalise);
    Vec2d dx = vecteur_vitesse*dt.asSeconds();
    setPosition(getPosition()+ dx);
}

bool AntKamikaze::isFighter() const
{
    return false;
}

AntKamikaze::~AntKamikaze()
{
    getAppEnv().addCompteur(s::KAMIKAZE_ANTS,-1);
}

void AntKamikaze::attacked(sf::Time dt)
{
    Animal::attacked(dt);
    if (isDead()) {
        getAppEnv().antKamikazeExplosion(getPosition());
    }
}
