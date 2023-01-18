/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#pragma once
#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "Animal.hpp"
#include "Food.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "FoodGenerator.hpp"
#include "Anthill.hpp"
#include "Pheromone.hpp"
#include <unordered_map>


class Environment : public Drawable, public Updatable
{
private:
    //attributs
    std::vector<Animal*> faune;
    std::vector<Food*> nourriture;
    FoodGenerator generateurFood;
    std::vector<Anthill*> fourmilieres;
    std::vector<Pheromone*> pheromones;
    bool pheromoneDisplay; //attribut indiquant si l'environnement doit se dessiner avec ou sans les traces de phéromones
    std::unordered_map<std::string, double> compteurs;
    double temperature;
public:
    //constructeurs
    Environment();
    Environment(Environment const&)=delete;
    //surcharge d'opérateurs
    Environment& operator=(Environment const&)=delete;

    //méthodes

    /*!
     * @brief ajoute une entité a la collection de l'environnement qui lui correspond
     *
     * @param pointeur sur l'entité
     */
    void addAnimal(Animal*);
    void addFood(Food*);
    void addAnthill (Anthill*);
    void addPheromone (Pheromone*); // à détruire dans le reset?

    /*!
     * @brief met a jour l'environnement ainsi que tout ce qu'il contient après chaque écoulement de temps dt
     *
     * @param temps dt
     */
    void update(sf::Time dt);

    /*!
     * @brief dessine l'environnement et son contenu (animal, food, anthill, pheromone)
     *
     * @param cible sur laquelle on dessine
     */
    void drawOn(sf::RenderTarget& targetWindow) const;

    /*!
     * @brief supprime tout l'environnement et désalloue la mémoire occupée par les pointeurs des différentes collections
     *
     */
    void reset();

    /*!
     * @brief trouver la source de nourriture la plus proche d'une fourmie
     *
     * @param position de la fourmie
     * @return le pointeur sur la source de food la plus proche de la fourmie
     */
    Food* getClosestFoodForAnt (ToricPosition const& position) const;

    /*!
     * @brief trouver la fourmilière la plus proche dans le rayon de perception d'une fourmie
     *
     * @param position de la fourmie
     * @return le pointeur sur la fourmilière en question
     */
    Anthill* getAnthillForAnt (ToricPosition const& position, Uid anthillId) const;

    /*!
     * \brief Change la valeur de l'attribut PheromonDisplay
     * \return
     */
    bool togglePheromoneDisplay();

    /*!
     * \brief Trouve les quantités de phéromones présentes autour de la fourmilière
     * \param position
     * \param direction_rad
     * \param angles
     * \return Un ensemble de phéromones correspondant à la quantité par intervalle du paramètre angles
     */
    Quantities getPheromoneQuantitiesPerIntervalForAnt (const ToricPosition &position, Angle direction_rad, Intervals angles) const;

    /*!
     * \brief Parcourt la faune pour trouver l'ennemi le plus proche de fighter
     * \param fighter
     * \return Un pointeur sur l'ennemi
     */
    Animal* getClosestEnemyforFighter(Animal* fighter) const;

    /*!
     * \brief Calcule les nouvellles données pour un graphe
     * \param Le libelle du graphe correspondant
     * \return Les données actualisées pour chaque courbe du graphe
     */
    std::unordered_map<std::string, double> fetchData(const std::string &libelle) const;

    /*!
      * \brief Avoir les titres des différentes anthills
      * \return Un vector contenant les différents Uids des anthills de l'environnement : "anthill #X"
      */
    std::vector<std::string> getAnthillsIds() const;

    /*!
     * \brief  met a jour le nombre d'animaux correspondant au libelle
     * \param  un entier i=1 ou -1 à appeler si un nouvel animal nait ou si une meurt
     */
    void addCompteur(std::string libelle, double d);


    //Extensions
    /*!
    * \brief Trouve la fourmilière ennemie la plus proche dans le rayon de perception de la fourmmi
    * \param position_fourmi
    * \param fourmi
    * \return Un pointeur sur cette fourmiliere
    */
    Anthill* getClosestEnemyAnthill(ToricPosition position_fourmi, Uid fourmi) const;

    /*!
     * \brief Les animaux dans le rayon d'explosion subissent des dégats et les fourmilieres sont détruites
     * \param La position de l'explosion
     */
    void antKamikazeExplosion(ToricPosition explosion);

    /*!
        * \brief permet de modifier la temperature
        * \param un entier i
        */
    void changeTemperature(int i);

    /*!
     * \brief permet d'obtenir la valeur de la temperature
     */
    double getTemperature() const;

    //destructeurs
    virtual ~Environment();



};

#endif // ENVIRONMENT_HPP
