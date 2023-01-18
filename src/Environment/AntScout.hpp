#ifndef ANTSCOUT_HPP
#define ANTSCOUT_HPP
#include "Ant.hpp"

enum EtatAntScout {Searching, Found};

class AntScout : public Ant
{
private:
    //attributs
    Angle directionEnemyAnthill;
    double distanceEnemyAnthill;
    EtatAntScout etatDeRecherche;
    ToricPosition homeAnthill;
    //méthode
    void setSearching ();
    void setFound (Angle, double);

public:
    //constructeur
    AntScout(ToricPosition tp, Uid f, ToricPosition home);
    //methodes
    virtual int getStrength() const override;
    void update(sf::Time dt) override;
    virtual bool isFighter() const override;
    virtual ~AntScout();


protected:
    virtual sf::Texture& getTexture() const override;
    virtual void debugDraw(sf::RenderTarget& target) const override;
};

#endif // ANTSCOUT_HPP
