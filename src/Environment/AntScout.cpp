#include "AntScout.hpp"
#include "Application.hpp"
#include "AntKamikaze.hpp"

//constructeur
AntScout::AntScout(ToricPosition tp, Uid f, ToricPosition home)
    :Ant (tp, f, getAppConfig().ant_scout_hp, getAppConfig().ant_scout_lifespan), etatDeRecherche(Searching), homeAnthill(home)
{
    getAppEnv().addCompteur(s::SCOUT_ANTS,1);
}

//methodes
int AntScout::getStrength() const
{
    return getAppConfig().ant_scout_strength;
}

void AntScout::update(sf::Time dt)
{
    Ant::update(dt);
    if(etatDeRecherche == Searching) {
        Anthill* closeEnemyAnthill= getAppEnv().getClosestEnemyAnthill(getPosition(), getAntUid());//cherche une fourmilière enemie

        if(closeEnemyAnthill!= nullptr) { //a trouvé une fourmilière enemie
            Vec2d chemin (homeAnthill.toricVector(closeEnemyAnthill->getPosition()));
            setFound(chemin.angle(), toricDistance(homeAnthill, closeEnemyAnthill->getPosition())); //radians ou degre ??
            antUturn();//fait un demi tour sur elle-même
        }
    } else {
        //Etat de Recherche == Found, elle rentre
        Anthill* closeAnthill = getAppEnv().getAnthillForAnt(getPosition(), getAntUid());
        if (closeAnthill != nullptr) {
            //Elle a trouvé sa maison, naissance d'une AntKamikaze
            //getAppEnv().addAnimal(new AntKamikaze(getPosition(), getAntUid(),directionEnemyAnthill,distanceEnemyAnthill));
            closeAnthill->setAttack(distanceEnemyAnthill,directionEnemyAnthill);
            setSearching();
        }

    }
}

sf::Texture& AntScout::getTexture() const
{
    return getAppTexture(getAppConfig().ant_scout_texture);
}

void AntScout::setSearching ()
{
    directionEnemyAnthill = 0;
    distanceEnemyAnthill = 0;
    etatDeRecherche = Searching;
}

void AntScout::setFound (Angle direction, double distance)
{
    directionEnemyAnthill = direction;
    distanceEnemyAnthill = distance;
    etatDeRecherche = Found;
}

bool AntScout::isFighter() const
{
    return false;
}

void AntScout::debugDraw(sf::RenderTarget& target) const
{
    Ant::debugDraw(target);
    auto const textEtat = buildText(to_nice_string(etatDeRecherche), getPosition().toVec2d()+Vec2d(30,15), getAppFont(), 30, sf::Color::Black);
    target.draw(textEtat);
}

AntScout::~AntScout()
{
    getAppEnv().addCompteur(s::SCOUT_ANTS,-1);
}
