/*
 * POOSV 2020-21
 * @author: Hortense LIARAS et Maud Dupont-Roc
 */

#include "ToricPosition.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include <cmath>
#include "../Utility/Vec2d.hpp"
#include <vector>


//méthodes
void ToricPosition::clamp()
{
    double X = fmod(coordonnees.x(), dimensions.x());
    if(X<0) {
        X+=dimensions.x();
    }
    double Y = fmod(coordonnees.y(), dimensions.y());
    if(Y<0) {
        Y+=dimensions.y();
    }
    coordonnees=Vec2d(X,Y);
}


//constructeurs
ToricPosition::ToricPosition ()
    : ToricPosition (0,0) {}

ToricPosition::ToricPosition(Vec2d const& coord, Vec2d const& dim)
    :coordonnees(coord), dimensions(dim)
{
    clamp();
}

ToricPosition::ToricPosition(double a, double b)
    :coordonnees(a, b), dimensions(getAppConfig().simulation_size, getAppConfig().simulation_size)
{
    clamp();
}

ToricPosition::ToricPosition(Vec2d const& coord)
    :coordonnees(coord), dimensions(getAppConfig().simulation_size, getAppConfig().simulation_size)
{
    clamp();
}

//métodes
Vec2d const& ToricPosition::toVec2d()
{
    return coordonnees;
}

double ToricPosition::x() const
{
    return coordonnees.x();
}
double ToricPosition::y() const
{
    return coordonnees.y();
}

//surcharge opérateurs
bool ToricPosition::operator==(ToricPosition const& T2)
{
    double X(coordonnees.x());
    double Y(coordonnees.y());
    return ((isEqual(X, T2.x())) and (isEqual(Y, T2.y())));
}

ToricPosition& ToricPosition::operator+=(ToricPosition const& T2)
{
    coordonnees=Vec2d(coordonnees.x()+T2.x(), coordonnees.y()+T2.y());
    clamp();
    return *this;
}

double ToricPosition::operator[](int index) const
{
    return coordonnees[index];
}

//méthode
Vec2d ToricPosition::toricVector(ToricPosition const& that) const
{
    double largeur_monde (dimensions.x());
    double hauteur_monde (dimensions.y());
    std::vector< std::vector <double> > tableau_dist(3, std::vector<double> (3));//tableau destiné à contenir toutes les distances des vecteurs candidats

    double min1 (distance (coordonnees, Vec2d(that.x(),that.y())));
    int deplacement_abscisse (0); //lignes de tableau_dist
    int deplacement_ordonnees (0); //colonnes de tableau_dist
    for(int i(-1); i<=1; ++i) { //2 boucles for permettants de représenter les 9 vecteurs possibles
        for(int j(-1); j<=1; ++j) {
            tableau_dist[i+1][j+1]=distance(this->coordonnees, Vec2d(that.x()+i*largeur_monde, that.y()+j*hauteur_monde)); //calcul de chaque distances
            if (tableau_dist[i+1][j+1] < min1) {
                min1 = tableau_dist[i+1][j+1];
                deplacement_abscisse = i;
                deplacement_ordonnees = j;
            }
        }
    }
    return((Vec2d(that.x(),that.y())+Vec2d(deplacement_abscisse*hauteur_monde,deplacement_ordonnees*largeur_monde))-this->coordonnees);
}


//surcharge opérateurs externe
ToricPosition operator+(ToricPosition T1, ToricPosition const& T2)
{
    T1+=T2;
    return T1;
}

std::ostream& operator<<(std::ostream& sortie, ToricPosition const& T1)
{
    sortie<<"["<<T1.x()<<", "<<T1.y()<<"]";
    return sortie;
}

//fonction
double toricDistance(ToricPosition const& from, ToricPosition const& to)
{
    return from.toricVector(to).length();
}

