/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#include "Environment.hpp"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Application.hpp"
#include "Utility/Types.hpp"
#include "Utility/Utility.hpp"
#include "Utility/Constants.hpp"

//destructeurs
Environment::~Environment()
{
    reset();
}

void Environment::reset()
{
    for(auto*& animals :faune) {
        delete animals;
    }
    faune.clear();
    for(auto*& food :nourriture) {
        delete food;
    }
    nourriture.clear();
    for(auto*& fourmiliere : fourmilieres) {
        delete fourmiliere ;
    }
    fourmilieres.clear();
    for(auto*& pheromone : pheromones) {
        delete pheromone;
    }
    pheromones.clear();
}

//méthodes
void Environment::addAnimal(Animal* ptr_animal)
{
    faune.push_back(ptr_animal);
}

void Environment::addFood(Food* ptr_food)
{
    nourriture.push_back(ptr_food);
}

void Environment::addPheromone (Pheromone* ptr_pheromone)
{
    pheromones.push_back(ptr_pheromone);
}

void Environment::addAnthill (Anthill* ptr_fourmiliere)
{
    fourmilieres.push_back(ptr_fourmiliere);
}

void Environment::update(sf::Time dt)  //a modifier
{
    //Update de faune
    for(auto*& animal :faune) {
        if(animal->isDead()) {
            delete animal;
            animal=nullptr;
        } else {
            animal->update(dt);
        }
    }
    faune.erase(std::remove(faune.begin(), faune.end(), nullptr), faune.end());

    //Update de generateurFood
    generateurFood.update(dt);

    //Update de nourriture
    for(auto*& food :nourriture) {
        if(food->isEmpty()) {
            delete food;
            food=nullptr;
        }
    }
    nourriture.erase(std::remove(nourriture.begin(), nourriture.end(), nullptr), nourriture.end());


    //Update de fourmilieres
    for(auto*& fourmiliere :fourmilieres) {
        fourmiliere->update(dt);
    }
    //update de pheromone
    for(auto*& pheromone: pheromones) {
        if(pheromone->isNegligible()) {
            delete pheromone;
            pheromone=nullptr;
        } else {
            pheromone->update(dt);
        }
    }
    pheromones.erase(std::remove(pheromones.begin(),pheromones.end(),nullptr), pheromones.end());
}

void Environment::drawOn(sf::RenderTarget& targetWindow) const
{
    for(auto* animal : faune) {
        animal->drawOn(targetWindow);
    }
    for(auto* food : nourriture) {
        food->drawOn(targetWindow);
    }
    for (auto* fourmiliere : fourmilieres) {
        fourmiliere->drawOn(targetWindow);
    }

    if(pheromoneDisplay) {
        for(auto* pheromone: pheromones) {
            pheromone->drawOn(targetWindow);
        }
    }
}

Food* Environment::getClosestFoodForAnt (ToricPosition const& position) const
{
    if(nourriture.empty()) {
        return nullptr;
    }
    Food* closeFood = closestFromPoint(position, nourriture);
    double distanceMin (toricDistance(position, closeFood->getPosition()));
    if (distanceMin <= getAppConfig().ant_max_perception_distance) {
        return closeFood;
    } else {
        return nullptr;
    }
}

Anthill* Environment::getAnthillForAnt (ToricPosition const& position, Uid anthillId) const
{
    if(fourmilieres.empty()) {
        return nullptr;
    }
    for (auto* fourmiliere : fourmilieres) {
        if ((fourmiliere->getEtat() != Destroyed) and (fourmiliere->getAnthillUid() == anthillId) and (toricDistance(position, fourmiliere->getPosition()) <= getAppConfig().ant_max_perception_distance)) {
            return fourmiliere;
        }
    }
    return nullptr;
}

bool Environment::togglePheromoneDisplay()
{
    if(pheromoneDisplay) {
        pheromoneDisplay=false;
    } else {
        pheromoneDisplay=true;
    }
    return pheromoneDisplay;
}



Quantities Environment::getPheromoneQuantitiesPerIntervalForAnt(const ToricPosition &position,Angle direction_rad, Intervals angles) const  //on a enlever la reference "&" pour angles, la remettre ???
{
    Quantities Q(angles.size(),0);
    for(size_t i(0); i<angles.size(); ++i) {
        normalise(angles[i]);
    }
    for(auto* pheromone: pheromones) {
        if(toricDistance(position, pheromone->getPosition())<=getAppConfig().ant_smell_max_distance) {
            Vec2d nu(position.toricVector(pheromone->getPosition()));
            Angle beta((nu.angle()-direction_rad)/DEG_TO_RAD);

            normalise(beta);//fonction définie dans utility
            Angle diffmin(400);
            size_t indice(0);
            for(size_t i(0); i<angles.size(); ++i) {
                Angle diff(std::abs(beta-angles[i]));
                if(diff<diffmin) {
                    diffmin=diff;
                    indice=i;
                }
            }
            Q[indice]+=pheromone->getQuantity();
        }

    }
    return Q;
}


Animal* Environment::getClosestEnemyforFighter(Animal* fighter) const
{
    double distanceMin (getAppConfig().animal_sight_distance + 50);
    Animal* closeEnemy = nullptr;
    for (auto* animal : faune) {
        //On vérifie que l'animal n'a pas été tué
        if (animal != nullptr) {
            if((fighter->isEnemy(animal)) and (animal->getEtat() == Idle)) {
                double distanceTemp (toricDistance(animal->getPosition(), fighter->getPosition()));
                if (distanceTemp < distanceMin) {
                    distanceMin = distanceTemp;
                    closeEnemy = animal;
                }
            }
        }
    }
    if (distanceMin <= getAppConfig().animal_sight_distance) {
        return closeEnemy;
    } else {
        return nullptr;
    }
}


std::unordered_map<std::string, double> Environment::fetchData(const std::string &libelle) const
{
    std::unordered_map<std::string, double> new_data;
    if (libelle == s::GENERAL) {
        new_data = compteurs;
        new_data.insert ( {s::ANTHILLS, fourmilieres.size()});
        new_data.insert({s::TEMPERATURE, getTemperature()});
    }
    if (libelle == s::FOOD) {
        new_data.insert({s::FOOD, nourriture.size()}) ;
    }
    if (libelle == s::ANTHILLS) {
        for (auto fourmiliere : fourmilieres) {
            new_data.insert({"anthill #"+to_nice_string(fourmiliere->getAnthillUid()),fourmiliere->getStock()});
        }
    }

    return new_data;
}


Anthill* Environment::getClosestEnemyAnthill (ToricPosition position_fourmi, Uid anthillId) const
{
    if(fourmilieres.empty()) {
        return nullptr;
    }
    for (auto* fourmiliere : fourmilieres) {
        if ((fourmiliere->getEtat() != Destroyed) and (fourmiliere->getAnthillUid() != anthillId) and (toricDistance(position_fourmi, fourmiliere->getPosition()) <= getAppConfig().ant_max_perception_distance)) {
            return fourmiliere;
        }
    }
    return nullptr;
}

void Environment::antKamikazeExplosion(ToricPosition explosion)
{
    for(auto* animal : faune) {
        if (toricDistance(explosion,animal->getPosition()) <= getAppConfig().ant_kamikaze_explosionradius) {
            animal->attacked(getAppConfig().ant_kamikaze_explosionstrength);
        }
    }
    for (auto*& fourmiliere : fourmilieres) {
        if ((fourmiliere->getEtat() != Destroyed) and (toricDistance(explosion,fourmiliere->getPosition()) <= getAppConfig().ant_kamikaze_explosionradius)) {
            fourmiliere->setDestroyed();
        }
    }
}

Environment::Environment()
    : temperature(20)
{
    compteurs = {
        {s::WORKER_ANTS, 0},
        {s::SOLDIER_ANTS, 0},
        {s::TERMITES, 0},
        {s::SCOUT_ANTS, 0},
        {s::KAMIKAZE_ANTS, 0}
    };
}

void Environment::addCompteur(std::string libelle, double d)
{
    compteurs[libelle] += d;

}

std::vector<std::string> Environment::getAnthillsIds() const
{
    std::vector<std::string> anthillIds;
    for (auto fourmiliere : fourmilieres) {
        anthillIds.push_back("anthill #"+to_nice_string(fourmiliere->getAnthillUid()));
    }
    return anthillIds;
}

void Environment::changeTemperature(int i)
{
    if(i==1) {
        if(temperature<getAppConfig().temperature_max) {
            temperature+=getAppConfig().temperature_delta;
        }
    }
    if(i==-1) {
        if(temperature>getAppConfig().temperature_min) {
            temperature-=getAppConfig().temperature_delta;
        }
    }
}

double Environment::getTemperature() const
{
    return temperature;
}


