/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#ifndef ANTHILL_HPP
#define ANTHILL_HPP
#pragma once
#include "../Utility/Types.hpp"
#include "Positionable.hpp"
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "Animal.hpp"


class Anthill : public Positionable, public Drawable, public Updatable
{
private:
    //attributs
    Quantity stock;
    Uid identifiant;
    sf::Time compteurGeneration;

    //Si la fourmilière est en mode attaque, elle va envoyer une fourmi kamikaze
    Etat etat;
    Angle directionEnemyAnthill;
    double distanceEnemyAnthill;

    //méthode
    /*!
     * \brief Retourne la probabilité d'apparition d'une AntWorker pour update
     * \return
     */
    Prob compute_WorkerProb() const;
    void debugDraw(sf::RenderTarget& target) const;
    Prob compute_ScoutProb() const;

public:
    //constructeur
    Anthill(ToricPosition tp);

    //méthodes
    void ajoutStock (Quantity q);
    void drawOn (sf::RenderTarget& target) const;

    /*!
     * \brief permet de générer des fourmis régulièrement
     * \param dt
     */
    void update (sf::Time dt);

    /*!
     * \brief permet d'obtenir l'identifiant de la fourmilière
     * \return
     */
    Uid getAnthillUid () const;

    /*!
     * \brief La fourmilière se prépare à générer une fourmi kamikaze
     * \param d pour la distance à la cible
     * \param a pour la direction de la cible
     */
    void setAttack(double d, Angle a);
    void setIdle();
    /*!
     * \brief La fourmilière s'est faite attaquer, elle ne peut plus générer de nouvelles fourmis
     */
    void setDestroyed();
    Quantity getStock() const;
    Etat getEtat() const;


    //destructeur
    virtual ~Anthill () {};

};

#endif // ANTHILL_HPP
