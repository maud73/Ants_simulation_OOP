/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#pragma once
#ifndef FOODGENERATOR_HPP
#define FOODGENERATOR_HPP
#include "../Utility/Utility.hpp"
#include "../Interface/Updatable.hpp"


class FoodGenerator : public Updatable
{
private:
    sf::Time compteur;
public:
    //constructeur
    /*!
     *@brief Constructeur par défaut, initialise compteur à sf::Time::Zero
     */
    FoodGenerator();

    //méthode
    /*!
     * @brief Augmente le compteur de dt et si compteur > seconds(getAppConfig().food_generator_delta) ajoute une source de nourriture à l'Environnement
     */
    void update(sf::Time dt);

    //destructeur
    virtual ~FoodGenerator() {};
};

#endif // FOODGENERATOR_HPP
