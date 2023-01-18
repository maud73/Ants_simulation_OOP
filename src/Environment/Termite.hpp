#ifndef TERMITE_HPP
#define TERMITE_HPP
#pragma once
#include "Animal.hpp"


class Termite : public Animal
{
public:
    Termite(ToricPosition tp);
    virtual double getSpeed() const override;
    virtual void drawOn(sf::RenderTarget& target) const override;
    virtual bool isEnemy (Animal const* entity) const override;
    virtual bool isEnemyDispatch (Termite const* other) const override;
    virtual bool isEnemyDispatch (Ant const* other) const override;
    virtual int getStrength() const override;
    virtual bool isFighter() const override;
    virtual sf::Time getAttackDelay() const override;
    virtual ~Termite();

protected:
    sf::Texture& getTexture() const;

};

#endif // TERMITE_HPP

