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
 * Cette classe sert à tester les combats entre animaux
 *
*/

class TermiteTest : public Application
{
public:
    TermiteTest(int argc, char const** argv)
        : Application(argc, argv)
    {
    }
    virtual ~TermiteTest() = default;
    virtual void onRun() override final;
    virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
protected:
    virtual std::string getHelpTextFile() const override final;
//	virtual void resetStats() override final;
};


