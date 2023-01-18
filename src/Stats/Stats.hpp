#ifndef STATS_HPP
#define STATS_HPP
#pragma once
#include <memory>
#include "Graph.hpp"
#include <vector>
#include "../Interface/Updatable.hpp"

class Stats : public Drawable, public Updatable
{
private:
    std::vector<std::unique_ptr<Graph>> graphes;
    std::vector<std::string> libelles;
    int idActif;
    sf::Time compteur;

public:
//constructeur
    Stats() ;
    Stats(Stats const&)=default;
//méthodes
    void setActive (int id);
    std::string getCurrentTitle() const;
    void next();
    void previous();
    void drawOn (sf::RenderTarget& target) const override;
    /*!
     * \brief update
     * \param dt
     */
    void update (sf::Time dt) override;
    /*!
     * \brief supprime toutes les données (les points) des graphes en utilisant Graph::reset()
     */
    void reset() ;
    /*!
     * \brief ????
     * \param id
     * \param title
     * \param series
     * \param min
     * \param max
     * \param size
     */
    void addGraph(int id, const std::string &title, const std::vector<std::string> &series, double min, double max, const Vec2d &size);
//destructeur
    virtual ~Stats() {};
};

#endif // STATS_HPP
