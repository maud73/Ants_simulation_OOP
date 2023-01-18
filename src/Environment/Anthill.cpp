/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "Anthill.hpp"
#include "../Random/Random.hpp"
#include "../Utility/Utility.hpp"
#include "Application.hpp"
#include "AntWorker.hpp"
#include "AntSoldier.hpp"
#include "AntScout.hpp"
#include "AntKamikaze.hpp"

//constructeur
Anthill::Anthill(ToricPosition tp)
    : Positionable(tp), stock (0), identifiant(createUid()), etat(Idle)  {}

//méthodes publiques
void Anthill::ajoutStock (Quantity q)
{
    stock += q;
}

void Anthill::drawOn (sf::RenderTarget& target) const
{
    double size (70);
    sf::Texture texture;
    if (etat == Destroyed) {
        size /= 1.5;
        texture = getAppTexture(getAppConfig().anthill_destroyed_texture);
    } else {
        texture = getAppTexture(getAppConfig().anthill_texture);
    }
    auto const anthillSprite = buildSprite(getPosition().toVec2d(),size, texture);
    target.draw(anthillSprite);
    if (isDebugOn()) {
        debugDraw(target);
    }
}
void Anthill::update (sf::Time dt)
{
    if (etat != Destroyed) {
        if (compteurGeneration >= sf::seconds(getAppConfig().anthill_spawn_delay)) {
            if(etat == Idle) {
                //Génération d'une fourmi normale
                double tirAuSort (uniform(0.0,1.0));
                if (tirAuSort < compute_ScoutProb()) {
                    getAppEnv().addAnimal(new AntScout(getPosition(), identifiant, getPosition()));
                } else {
                    if (uniform(0.0,1.0) < compute_WorkerProb()) {
                        getAppEnv().addAnimal(new AntWorker(getPosition(), identifiant));
                    } else {
                        getAppEnv().addAnimal(new AntSoldier(getPosition(), identifiant));
                    }
                }

            } else {
                //Etat == Attack : lance une kamikaze
                getAppEnv().addAnimal(new AntKamikaze(getPosition(), getAnthillUid(),directionEnemyAnthill,distanceEnemyAnthill));
                setIdle();
            }
            //Remise à zéro du compteur
            compteurGeneration = sf::Time::Zero;
        }
        compteurGeneration += dt;
    }
}

//méthode privées
Prob Anthill::compute_WorkerProb() const
{
    return getAppConfig().anthill_worker_prob_default;
}

Prob Anthill::compute_ScoutProb() const
{
    return getAppConfig().anthill_scout_prob_default;
}

void Anthill::debugDraw(sf::RenderTarget& target) const
{
    auto const textStock = buildText(to_nice_string(stock), getPosition().toVec2d()+Vec2d(30,15), getAppFont(), 30, sf::Color::Black);
    target.draw(textStock);
    auto const textIdentifiant = buildText(to_nice_string(getAnthillUid()), getPosition().toVec2d()+Vec2d(30,-15), getAppFont(), 30, sf::Color::Magenta);
    target.draw(textIdentifiant);
}

Uid Anthill::getAnthillUid () const
{
    return identifiant;
}

void Anthill::setAttack(double d, Angle a)
{
    etat = Attack;
    distanceEnemyAnthill = d;
    directionEnemyAnthill = a;
}

void Anthill::setIdle()
{
    etat = Idle;
    distanceEnemyAnthill = 0;
    directionEnemyAnthill = 0;
}

Quantity Anthill::getStock() const
{
    return stock;
}

void Anthill::setDestroyed()
{
    etat = Destroyed;
    stock = 0;
}

Etat Anthill::getEtat() const
{
    return etat;
}
