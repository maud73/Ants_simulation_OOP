#include "Loader.hpp"
#include <iostream>
#include <fstream>
#include "../Application.hpp"
#include "Termite.hpp"



void Loader::loadMap (std::string const& filepath)
{
    //Lire ligne à ligne le fichier filepath
    std::ifstream entree;
    entree.open(filepath);
    while (! entree.eof()) {
        if (!entree.fail()) {
            //1er mot
            std::string entite;
            entree >> entite;
            if (entite.front() == '#') {
                //On ignore la ligne
                getline(entree, entite);
                entree.clear();
            } else {
                double posX;
                double posY;
                entree >> posX >> posY;
                if(entite == "anthill") {
                    getAppEnv().addAnthill(new Anthill(ToricPosition(posX,posY)));
                }
                if (entite == "food") {
                    Quantity quantite;
                    entree >> quantite;
                    getAppEnv().addFood(new Food(ToricPosition(posX,posY), quantite));
                }
                if (entite == "termite") {
                    getAppEnv().addAnimal(new Termite(ToricPosition(posX,posY)));
                }
            }
        }
    }
    entree.close();
}
