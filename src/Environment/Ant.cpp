/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "Ant.hpp"
#include "../Application.hpp"
#include"Pheromone.hpp"
#include"Utility/Utility.hpp"


//constructeur
Ant::Ant (ToricPosition tp, Uid f, int pv, int ev)
    : Animal (tp, pv, ev), fourmiliere (f), P0(tp) {}

//méthodes
double Ant::getSpeed() const
{
    double speed(getAppConfig().ant_speed);
    if(getAppEnv().getTemperature()>=30) {
        speed/=2;
    }
    return speed;
}

void Ant::drawOn(sf::RenderTarget& target) const
{
    sf::Sprite antSprite = buildSprite (getPosition().toVec2d(), 30, getTexture());
    antSprite.setRotation(getDirection()/DEG_TO_RAD);
    target.draw(antSprite);
    if(isDebugOn()) {
        debugDraw(target);

    }
}


void Ant::spreadPheromones ()
{
    Vec2d dx(P0.toricVector(getPosition()).normalised());
    auto distance(toricDistance(P0, getPosition()));
    int  nombrePheromones (getAppConfig().ant_pheromone_density*distance); //CORRECT
    double espacePheromones (distance/nombrePheromones);
    for (int i (0); i < nombrePheromones ; ++i) {
        P0 += dx*espacePheromones;
        getAppEnv().addPheromone(new Pheromone(P0, getAppConfig().ant_pheromone_energy));
    }
}

RotationProbs Ant::computeRotationProbs()const
{

    Probs Pm2(11);
    Quantities Q(getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(),getDirection(),I));
    Probs Pm({ 0.0000, 0.0000, 0.0005, 0.0010, 0.0050, 0.9870, 0.0050, 0.0010, 0.0005, 0.0000, 0.0000 });
    Probs Pphi(11);
    double somme(0);
    for(size_t i(0); i<11; ++i) {
        Pphi[i]=1/(1+exp(-getAppConfig().beta_d*(Q[i]-getAppConfig().q_zero)));
        somme+=Pphi[i];
    }
    for(auto& proba: Pphi) {
        proba/=somme;
    }
    double Z(0);
    for(size_t i(0); i<11; ++i) {
        Pm2[i]=pow(Pphi[i],getAppConfig().alpha)*Pm[i];
        Z+=Pm2[i];
    }
    for(auto& probaFinal: Pm2) {
        probaFinal/=Z;
    }
    return std::pair <Intervals, Probs> (I, Pm2);
}

void Ant::affichageProbaRotation(sf::RenderTarget& target)const
{
    //Déclarer une constante pour les intervalles
    auto const intervalProbs = computeRotationProbs();
    // pour intervalProbs (first désigne l'ensemble des angles)

    for (std::size_t i = 0; i < intervalProbs.first.size(); ++i) {
        // "second" designe l'ensemble des probabilités
        auto const msg = std::to_string(intervalProbs.second[i]).substr(2, 4);
        auto const angle = intervalProbs.first[i];
        auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 250;

        auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Black);
        target.draw(text);
    }
    auto intervals(intervalProbs.first);
    auto const quantities = getAppEnv().getPheromoneQuantitiesPerIntervalForAnt(getPosition(), getDirection(), intervals);
    for (std::size_t i = 0; i < quantities.size(); ++i) {
        auto const msg = std::to_string(quantities[i]).substr(0, 4);
        auto const angle = intervals[i];
        auto const local = Vec2d::fromAngle(getDirection() + angle * DEG_TO_RAD) * 200;

        auto const text = buildText(msg, getPosition().toVec2d() + local, getAppFont(), 15, sf::Color::Red);
        target.draw(text);
    }
}

void Ant::update(sf::Time dt)
{
    Animal::update(dt);
    spreadPheromones();
}

Uid Ant::getAntUid() const
{
    return fourmiliere;
}

void Ant::antUturn()
{
    setDirection(getDirection()+PI);
}

void Ant::debugDraw(sf::RenderTarget& target) const
{
    Animal::debugDraw(target);
    affichageProbaRotation(target);
    sf::CircleShape circleSmell = buildAnnulus(getPosition().toVec2d(), getAppConfig().ant_smell_max_distance, sf::Color::Blue, 5);
    target.draw(circleSmell);
}

sf::Time Ant::getAttackDelay() const
{
    return sf::seconds(getAppConfig().ant_attack_delay);
}

bool Ant::isEnemy (Animal const* entity) const
{
    return entity->isEnemyDispatch(this);
}

bool Ant::isEnemyDispatch (Termite const*) const
{
    return true;
}

bool Ant::isEnemyDispatch (Ant const* other) const
{
    if(this->getAntUid()==other->getAntUid()) {
        return false;
    } else {
        return true;
    }
}
