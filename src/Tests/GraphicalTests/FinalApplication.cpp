/*
 * POOSV 2020-21
 * Marco Antognini & Jamila Sam
 */

#include <Config.hpp>
#include <Environment/Environment.hpp>
// UNCOMMENT AT STEP 5.2
//#include <Environment/Loader.hpp>
#include <Environment/Anthill.hpp>
#include <Environment/AntWorker.hpp>
#include <Environment/AntSoldier.hpp>
#include <Environment/Termite.hpp>
#include <Utility/Utility.hpp>
#include "FinalApplication.hpp"

#include <cassert>

IMPLEMENT_MAIN(FinalApplication);

void FinalApplication::onRun()
{
    // Basic setup
    Application::onRun();
    // add graphs for statistics
    setStats(true);
    resetStats();
}

void FinalApplication::onSimulationStart()
{
    Application::onSimulationStart();
}

void FinalApplication::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        default:
            break;
        case sf::Keyboard::M:
            /*
              // UNCOMMENT WHEN READY TO USE
            getAppEnv().reset();
            loadMap(getResPath() + getAppConfig().map_name);
            resetStats();
            */
            break;
        case sf::Keyboard::P:
            getAppEnv().togglePheromoneDisplay();
            break;
        case sf::Keyboard::H:
            getAppEnv().addAnthill(new Anthill(getCursorPositionInView()));
            resetStats();
            break;
        case sf::Keyboard::W:
            getAppEnv().addAnimal(new AntWorker(getCursorPositionInView(), createUid()));
            break;
        case sf::Keyboard::S:
            getAppEnv().addAnimal(new AntSoldier(getCursorPositionInView(), createUid()));
            break;
        case sf::Keyboard::T:
            getAppEnv().addAnimal(new Termite(getCursorPositionInView()));
            break;
        }

    }
}
void FinalApplication::resetStats()
{
    Application::resetStats();
    addGraph(s::GENERAL, { s::WORKER_ANTS, s::SOLDIER_ANTS, s::TERMITES,s::TEMPERATURE, s::SCOUT_ANTS, s::KAMIKAZE_ANTS}, 0, 100);
    addGraph(s::FOOD,  { s::FOOD }, 0, 1000);
    const auto anthills_titles(getAppEnv().getAnthillsIds());
    addGraph(s::ANTHILLS, anthills_titles, 0, 100);
    setActiveGraph(0);
}


