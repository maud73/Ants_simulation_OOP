#ifndef LOADER_HPP
#define LOADER_HPP

#pragma once
#include <string>

class Loader
{
public:
//constructeur
    Loader() = default;
//méthodes
    /*!
     * \brief Ajoute des éléments dans l'environnement selon les instructions d'un fichier texte
     * Les lignes du fichier texte commençant par un '#' sont condidérés comme commentaires
     * Le premier mot de la ligne correspond à l'entité qu'on veut ajouter ("anthill", "food" ou "termite")
     * Ensuite il y a 2 double pour la position en x et en y de notre entité (et un 3ème doublee pour la quantité lorsqu'on créé un "food")
     * \param filepath pour le chemin d'accès au fichier texte
     */
    void loadMap (std::string const& filepath);
//destructeur
    ~Loader() {};
};

#endif // LOADER_HPP
