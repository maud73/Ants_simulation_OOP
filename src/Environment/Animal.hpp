/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#pragma once
#ifndef ANIMAL_HPP
#define ANIMAL_HPP
#include "../Utility/Types.hpp"
#include "Positionable.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/Utility.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"

class Ant;
class Termite;
enum Etat {Attack, Idle, Destroyed};

const Intervals I({   -180,   -100,    -55,    -25,    -10,      0,     10,     25,     55,    100,    180 });

class Animal:public Positionable, public Drawable, public Updatable
{
private:
    Angle angleDirection;
    int pointsVie;
    int esperanceVie;
    sf::Time compteurRotation;
    Etat etat;
    Animal* enemy;
    sf::Time compteurCombat;

//méthode
    /*!
     * \brief L'ennemi oublie que this est son ennemi
     */
    void forfeit();

public:
    //méthodes

    virtual double getSpeed() const = 0;

    /*!
     * @brief obtenir la direction de l'animal
     *
     * @return l'attribut angleDirection
     */
    Angle getDirection() const;

    /*!
     * @brief Controle si l'animal est vivant
     *
     * @return true si esperanceVie ou pointsVie sont =< 0
     */
    bool isDead() const;

    /*!
     * @brief Dessine l'animal
    */
    virtual void drawOn(sf::RenderTarget& target) const = 0;

    //constructeurs
    /*!
       * @brief Constructeur n°1: initialise un animal avec les valeurs passées en paramètre et angleDirection = 0
       *
       * @param  position tp, pointsVie pv et esperanceVie ev
       */
    Animal (ToricPosition tp, int pv, int ev);

    /*!
     * @brief Constructeur n°2: Initialise un Animal avec le constructeur n°1 tel que Animal(tp, 1, getAppConfig().animal_default_lifespan)
     *
     * @param ToricPosition tp pour la position
     */
    Animal (ToricPosition tp);

    //méthodes

    /*!
     * @brief Fais avancer l'état de l'animal dans la simulation
     *
     * @param Temps durant lequel l'animal évolue
     */
    void update (sf::Time dt);

    /*!
     * \brief permet de savoir si deux animaux sont ennemis afin d'engager ou non le combat
     * \param entity qui est un animal
     * \return oui ou non suivant si les animaux testés sont enemis ou non
     */
    virtual bool isEnemy (Animal const* entity) const = 0;

    /*!
     * \brief isEnemyDispatch sont deux fonctions ayant des types d'arguments différents et permettent d'obtenir la valeur de retour de isEnemy sans faire de comparaison de types
     * \param other qui peut être une termite ou une fourmi
     * \return la réponse si oui ou non les deux animaux sont enemis
     */
    virtual bool isEnemyDispatch (Termite const* other) const = 0;
    virtual bool isEnemyDispatch (Ant const* other) const =0;

    virtual int getStrength() const =0;

    /*!
     * \brief permet de savoir si un animal est en mode attack ou idle
     * \return son etat
     */
    Etat getEtat() const;

    /*!
     * \brief L'animal reçoit des dégats
     * \param degat
     */
    virtual void attacked (int degat);

    //destructeur
    virtual ~Animal();

protected:
    void setDirection(Angle);

    /*!
     * @brief Déplace un animal en lui faisant éventuellement subir une rotation
     *
     * @param Temps durant lequel l'animal se déplace
     */
    virtual void move(sf::Time dt);

    /*!
     * @brief Pour avoir les probabilités de rotation
     *
     * @return un pair d'ensemble des angles de rotation que l'animal peut subir associé avec l'ensemble de probabilités de ces roations
     */
    virtual RotationProbs computeRotationProbs()const;

    /*!
     * @brief Dessine l'animal avec son angle de direction et son espérance de vie
     *
     * @param target sur laquelle on dessine
     */
    void debugDraw(sf::RenderTarget& target) const;

    virtual bool isFighter() const =0;

    /*!
     * \brief L'animal est attaqué par son ennemi en subissant des dégats
     * \param dt pour incrémenter le compteurCombat
     */
    virtual void attacked(sf::Time dt);

    virtual sf::Time getAttackDelay() const =0;

    /*!
     * \brief Bascule l'état de this en Attack et enregistre other comme enemy
     * \param other
     */
    void setAttack (Animal* other);

    /*!
     * \brief Bascule l'état de this en Idle et garde un nullptr comme enemy
     * \brief Remet le compteurCombat à zéro
     */
    void setIdle ();



};

#endif // ANIMAL_HPP



