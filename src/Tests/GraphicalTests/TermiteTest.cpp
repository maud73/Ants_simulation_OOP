/*
 * POOSV
 * 2020-21
 * Marco Antognini
 */

#include <Config.hpp>
#include <Environment/Environment.hpp>
#include <Environment/Anthill.hpp>
#include <Environment/Termite.hpp>
#include <Environment/AntWorker.hpp>
#include <Environment/AntSoldier.hpp>
#include <Utility/Utility.hpp>
#include "TermiteTest.hpp"

IMPLEMENT_MAIN(TermiteTest)

void TermiteTest::onRun()
{
    // Basic setup
    Application::onRun();
    // add graphs for statistics
    setStats(false);
    //resetStats();
}


std::string TermiteTest::getHelpTextFile() const
{
    return RES_LOCATION + "termite-test-help.txt";
}

void TermiteTest::onEvent(sf::Event event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        default:
            break;
        case sf::Keyboard::T:
            getAppEnv().addAnimal(new Termite(getCursorPositionInView()));
            break;
        case sf::Keyboard::W:
            getAppEnv().addAnimal(new AntWorker(getCursorPositionInView(), createUid()));
            break;
        case sf::Keyboard::S:
            getAppEnv().addAnimal(new AntSoldier(getCursorPositionInView(),  createUid()));
            break;
        case sf::Keyboard::H:
            getAppEnv().addAnthill(new Anthill(getCursorPositionInView()));
            break;
        case sf::Keyboard::P:
            getAppEnv().togglePheromoneDisplay();
            break;
        }

    }
}

/*
void TermiteTest::resetStats()
{
	Application::resetStats();
	addGraph(s::GENERAL, { s::WORKER_ANTS, s::SOLDIER_ANTS, s::TERMITES ,s::TEMPERATURE}, 0, 100);
	setActiveGraph(0);
}
*/
