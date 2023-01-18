/*
 *  POOSV
 * 2020-21
 * Marco Antognini & Jamila Sam
 */
#pragma once

#include <Application.hpp>
#include <Environment/Environment.hpp>


class Ant;
/*
 * Cette classe sert à tester que les fourmis parviennent à ramener de la nourriture à
 * leur fourmilière en suivant les traces de phéromone.
 *
*/

class AntTest : public Application
{
public:
    AntTest(int argc, char const** argv)
        : Application(argc, argv)
    {
    }
    virtual ~AntTest() = default;
    virtual void onRun() override final;
    virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
protected:
    virtual std::string getHelpTextFile() const override final;
    //virtual void resetStats() override final;
};


