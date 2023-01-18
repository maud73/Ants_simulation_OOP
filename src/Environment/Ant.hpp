#ifndef ANT_HPP
#define ANT_HPP
#pragma once
#include "Animal.hpp"


class Ant : public Animal
{
private:
    //attributs
    Uid fourmiliere;
    ToricPosition P0;

public:
    //constructeur
    Ant(ToricPosition tp, Uid f, int pv, int ev);

    //méthodes
    double getSpeed() const override;

    /*!
     * \brief Dessine les fourmis avec la texture adaptée
     * \param target sur laquelle on dessine
     */
    void drawOn(sf::RenderTarget& target) const override final;

    /*!
     * \brief correspond à l'algorithme permettant le dépot des pheromones
     */
    void spreadPheromones ();

    /*!
     * \brief adaptation de la méthode au déplacement sensoriel: les fourmis doivent suivrent les phéromones déposées
     * \return les probabilités de déplacement pour chaque anlgle considéré
     */
    virtual RotationProbs computeRotationProbs() const override;

    Uid getAntUid() const;

    /*!
     * \brief les fourmis se comportent comme les autres animaux mais suivent et dispersent des phéromones
     * \param dt
     */
    void update(sf::Time dt) override;

    /*!
     * \brief Permet l'affichage des probabilités de rotation autour de la fourmie si l'on est en mode debug
     * \param affichage autour de la cible target
     */
    void affichageProbaRotation(sf::RenderTarget& target) const;

    virtual bool isEnemy (Animal const* entity) const override final;
    virtual bool isEnemyDispatch (Termite const* other) const override final;
    virtual bool isEnemyDispatch (Ant const* other) const override final;
    virtual int getStrength() const override=0;


protected:
    //méthodes
    virtual sf::Texture& getTexture() const =0;

    /*!
     * \brief fait faire une rotation sur elle-même à la fourmi
     */
    void antUturn();

    virtual void debugDraw(sf::RenderTarget& target) const;

    /*!
     * \brief donne la durée durant laquelle un animal reste en mode attack
     * \return une durée
     */
    virtual sf::Time getAttackDelay() const override;


};

#endif // ANT_HPP
