#include "Stats.hpp"
#include "Graph.hpp"
#include <Application.hpp>
#include "../Random/Random.hpp"
#include <unordered_map>
#include "../Environment/Environment.hpp"


//constructeurs
Stats::Stats()
    : compteur(sf::Time::Zero)
{}

//méthodes
void Stats::setActive (int id)
{
    if((id>=0) and (id<graphes.size())) {
        idActif=id;
    }
}

std::string Stats::getCurrentTitle() const
{
    return libelles[idActif];
}

void Stats::next()
{
    idActif+=1;
    if (idActif>=graphes.size()) {
        idActif=0;
    }
}

void Stats::previous()
{
    idActif-=1;
    if(idActif<0) {
        idActif=(graphes.size()-1);
    }
}

void Stats::drawOn (sf::RenderTarget& target) const
{
    graphes[idActif]->drawOn(target);
}



void Stats::update (sf::Time dt)
{
    compteur+=dt;
    if(compteur>sf::seconds(getValueConfig()["stats"]["refresh rate"].toDouble())) {

        for(size_t i(0); i<graphes.size(); ++i) {
            graphes[i]->updateData(compteur, getAppEnv().fetchData(libelles[i]));
        }
        compteur = sf::Time::Zero;
    }
}

void Stats::reset()
{
    for(size_t i(0); i<graphes.size(); ++i) {
        graphes[i].reset();
    }
}

void Stats::addGraph(int id, const std::string &title, const std::vector<std::string> &series, double min, double max, const Vec2d &size)
{
    //créer les cases vides
    while (graphes.size() <= id) {
        graphes.push_back(nullptr);
        libelles.push_back(" ");
    }
    graphes[id].reset(new Graph(series, size, min, max));
    libelles[id]=title;
    idActif=id;
}


