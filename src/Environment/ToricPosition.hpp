/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud DUPONT-ROC
 */

#pragma once
#include "../Utility/Vec2d.hpp"
#include <ostream>
#include <cmath>

/*!
 * @brief Handle toric coordinate, distance and other
 * basic math operation in a toric world
 *
 * @note Gets the dimensions of the world from getAppConfig()
 */

class ToricPosition
{
private:
    //attributs
    Vec2d coordonnees;
    Vec2d dimensions;

    //méthodes
    /*!
     *  @brief Projette le Vec2d de coordonnees du ToricPosition dans un monde torique
     */
    void clamp();

public:
    //constructeurs

    /*!
     * @brief Constructeur n°1 : par défaut
     *
     * @return Construit un ToricPosition en utilisant le Constructeur n°3 avec (0,0) en paramètres
     */
    ToricPosition();

    ToricPosition(Vec2d const& coord, Vec2d const& dim);

    /*!
     * @brief Constructeur n°3
     *
     * @param 2 double pour la position
     * @return Construit un ToricPosition avec en position les paramètres et en dimension un monde carré de côté getAppConfig().simulation_size
     */
    ToricPosition(double, double);


    /*!
     * @brief Constructeur n°4
     *
     * @param Vec2d pour la position
     * @return Construit un ToricPosition avec en position les paramètres et en dimension un monde carré de côté getAppConfig().simulation_size
     */
    ToricPosition(Vec2d const& coord);


    /*!
     * @brief Constructeur n°5 : constructeur de copie
     *
     * @param ToricPosition
     * @return Constructeur de copie par défaut
     */
    ToricPosition(ToricPosition const&)= default;

    //surcharge opérateurs
    ToricPosition& operator=(ToricPosition const&) = default;

    //métodes

    /*!
     * @brief Convertit le ToricPosition en Vec2d
     *
     * @return l'attribut coordonees
     */
    Vec2d const& toVec2d();

    double x() const;
    double y() const;

    //surcharge opérateurs
    bool operator==(ToricPosition const&);
    ToricPosition& operator+=(ToricPosition const&);


    /*!
     * @brief Opérateur d'indice
     *
     * @param int : 0 ou 1
     * @return coordonnes x (0) ou y (1)
     */
    double operator[](int index) const;

    //méthode

    /*!
     * @brief Trouver le plus petit vecteur jusqu'à that en prenant en compte qu'on se déplace dans un monde torique
     *
     * @param ToricPosition that vers lequel on veut aller
     * @return Le plus petit vecteur de l'instance this à that
     */
    Vec2d toricVector(ToricPosition const& that) const;

};

//surcharge opérateurs externe
ToricPosition operator+(ToricPosition T1, ToricPosition const& T2);
std::ostream& operator<<(std::ostream&, ToricPosition const&);

//fonction

/*!
 * @brief Trouver la plus courte distance entre from et to en prenant en compte qu'on se déplace dans un monde torique
 *
 * @param 2 ToricPosition : from et to
 * @return la distance dans le monde torique from-to
 */
double toricDistance(ToricPosition const& from, ToricPosition const& to);



