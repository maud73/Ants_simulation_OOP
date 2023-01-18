/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "FoodGenerator.hpp"
#include <Application.hpp>
#include "../Random/Random.hpp"

//constructeur
FoodGenerator::FoodGenerator()
    :compteur(sf::Time::Zero) {}

//méthode
void FoodGenerator::update(sf::Time dt)
{
    compteur+=dt;
    if(compteur>sf::seconds(getAppConfig().food_generator_delta)) {
        compteur = sf::Time::Zero;
        double tp_x(normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4));
        double tp_y(normal(getAppConfig().simulation_size/2, getAppConfig().simulation_size/4*getAppConfig().simulation_size/4));
        Quantity q(uniform(getAppConfig().food_min_qty, getAppConfig().food_max_qty));
        getAppEnv().addFood(new Food(ToricPosition(tp_x, tp_y), q));
    }
}
