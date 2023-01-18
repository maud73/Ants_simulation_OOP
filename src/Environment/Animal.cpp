/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "Animal.hpp"
#include "../Application.hpp"
#include "../Random/Random.hpp"

//méthodes publiques
Angle Animal::getDirection() const
{
    return angleDirection;
}

bool Animal::isDead() const
{
    if (pointsVie <= 0 or esperanceVie <= 0) {
        return true;
    } else {
        return false;
    }
}

//constructeurs
Animal::Animal(ToricPosition tp, int pv, int ev)
    : Positionable(tp), angleDirection (uniform(0.0, TAU)), pointsVie(pv), esperanceVie (ev), compteurRotation(), etat (Idle), enemy(nullptr) {} //Constructeur par défaut de sf::Time l'initialise à 0;

Animal::Animal(ToricPosition tp)
    : Animal (tp, 1, getAppConfig().animal_default_lifespan) {}

//méthode protected
void Animal::setDirection(Angle a)
{
    angleDirection = a;
}

//méthodes
void Animal::move(sf::Time dt)
{
    if (compteurRotation >= sf::seconds(getAppConfig().animal_next_rotation_delay)) { //
        //Tentative de rotation
        Intervals thetas (computeRotationProbs().first);
        Probs probas (computeRotationProbs().second);
        std::piecewise_linear_distribution<> dist (thetas.begin(), thetas.end(), probas.begin());
        Angle rotation = dist(getRandomGenerator())*DEG_TO_RAD;
        angleDirection += rotation;
        compteurRotation = sf::Time::Zero;
    }
    compteurRotation += dt;
    Vec2d vecteur_direction_normalise = Vec2d::fromAngle(getDirection()).normalised();
    Vec2d vecteur_vitesse (getSpeed()*vecteur_direction_normalise);
    Vec2d dx = vecteur_vitesse*dt.asSeconds();
    setPosition(getPosition()+ dx);
}

void Animal::update(sf::Time dt)
{
    esperanceVie -= 1;
    if (etat==Idle) {
        if (isFighter()) {
            //Cherhce un ennemi
            Animal* closeEnemy = getAppEnv().getClosestEnemyforFighter(this);
            if (closeEnemy != nullptr) {
                //Engage le combat
                this->setAttack(closeEnemy);
                this->enemy->setAttack(this);
            } else {
                //il n'y a pas d'ennemi aux alentours, il avance normalement
                move(dt);
            }
        } else {
            //Ce n'est pas un attaquant et il est en état neutre, donc il avance
            move(dt);
        }
    }
    if (etat == Attack) {
        //Vérifie que les compteurs ne soient pas dépassés
        if ((this->compteurRotation >= getAttackDelay()) or(this->enemy->compteurRotation >= getAttackDelay())) {
            //Arrêt du combat phase 1 : éloignement
            if (toricDistance(this->getPosition(),this->enemy->getPosition()) <= getAppConfig().animal_sight_distance) {
                this->move(dt);
            } else {
                //Arrêt du combat phase 2 : mode Idle, les ennemis s'oublient
                this->enemy->setIdle();
                this->setIdle();
            }
        } else {
            /*Attaque : this subit l'attaque, et quand Environment::update itérera sur l'ennemi il subira à son tour l'attaque
             *
             * Manière moins évidente de représenter une attaque mais facilite l'encapsulation :
             * on a mémorisé l'ennemi dans this, et on utilise la méthode getStrength
             * permet d'utiliser la même méthode pour les combattants et les non-combattants
             */
            this->attacked(dt);
        }
    }
}

RotationProbs Animal::computeRotationProbs() const
{
    Probs probas = {0.0000,0.0000,0.0005,0.0010,0.0050,0.9870,0.0050,0.0010,0.0005,0.0000,0.0000};
    return std::pair <Intervals, Probs> (I, probas); //I définit comme constante dans Animal.hpp
}

void Animal::debugDraw(sf::RenderTarget& target) const
{
    auto const text = buildText(to_nice_string(esperanceVie), getPosition().toVec2d()+Vec2d(20,10), getAppFont(), 30, sf::Color::Red);
    target.draw(text);
    sf::VertexArray ligneDirection (sf::PrimitiveType::Lines, 2);
    ligneDirection[0] = { getPosition().toVec2d(), sf::Color::Black };
    ligneDirection[1] = { getPosition().toVec2d()+ Vec2d::fromAngle(getDirection())*100, sf::Color::Blue };
    target.draw(ligneDirection);
}

Etat Animal::getEtat() const
{
    return etat;
}

void Animal::setAttack (Animal* other)
{
    this->etat = Attack;
    this->enemy = other;
}

void Animal::attacked(sf::Time dt)
{
    this->pointsVie -= enemy->getStrength();
    compteurCombat += dt;
}

void Animal::setIdle()
{
    this->etat = Idle;
    this->enemy = nullptr;
    compteurCombat = sf::Time::Zero;
}

void Animal::forfeit()
{
    if (enemy!= nullptr) {
        enemy->setIdle();
    }
}

Animal::~Animal()
{
    forfeit();
}

void Animal::attacked(int degat)
{
    this->pointsVie -= degat;
}


