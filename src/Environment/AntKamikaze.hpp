#ifndef ANTKAMIKAZE_HPP
#define ANTKAMIKAZE_HPP
#include "Ant.hpp"


class AntKamikaze : public Ant
{
private:
    sf::Time decompteExplosion;


public:
    AntKamikaze(ToricPosition tp, Uid f, Angle direction, double distance);
    //methodes

    /*!
     * \brief Update provoque une explosion si le décompte de l'explosion atteint 0
     * \param dt pour décrementer le décompte de l'explosion
     */
    void update(sf::Time dt) override;

    virtual int getStrength() const override;
    virtual bool isFighter() const override;

    //destructeur
    virtual ~AntKamikaze();

protected:
    virtual sf::Texture& getTexture() const override;

    /*!
     * \brief AntKamikaze avancent comme les autres animaux mais ne tentent pas de rotations
     * \param dt
     */
    virtual void move(sf::Time dt) override;

    /*!
     * \brief Si la kamikaze se fait attaquer au point que sa vie soit menacée, il provoque une explosion
     * \param dt
     */
    virtual void attacked(sf::Time dt) override;
};

#endif // ANTKAMIKAZE_HPP
