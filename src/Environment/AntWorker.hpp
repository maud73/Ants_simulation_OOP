/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#ifndef ANTWORKER_HPP
#define ANTWORKER_HPP
#pragma once
#include "Ant.hpp"


class AntWorker : public Ant
{
private:
    //attributs
    Quantity stock;
public:
    //constructeur

    /*!
     * \brief Initialise une AntWorker avec les valeurs en paramètres et des points de vie et une espérance de vie venant de getAppConfig
     * \param tp
     * \param f
     */
    AntWorker(ToricPosition tp, Uid f);

    //méthodes

    /*!
     * \brief update en utilisant Animal::update puis :
     *          si elle transporte de la nourriture : cherche sa fourmilière pour y déposer son stock
     *          si elle n'en transporte pas : cherche une source de nourriture pour récupérer de la nourriture
     * \param dt
     */
    virtual void update(sf::Time dt) override;
    virtual int getStrength() const override;
    virtual bool isFighter() const override;
    //destructeur
    virtual ~AntWorker();

protected:
    sf::Texture& getTexture() const override;
    virtual void debugDraw(sf::RenderTarget& target) const override;

};


#endif // ANTWORKER_HPP
