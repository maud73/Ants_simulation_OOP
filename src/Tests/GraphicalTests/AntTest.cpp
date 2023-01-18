/*
 * POOSV
 * 2020-21
 * Marco Antognini
 */

#include <Config.hpp>
#include <Environment/Environment.hpp>
#include <Environment/AntWorker.hpp>
#include <Environment/AntSoldier.hpp>
#include <Utility/Utility.hpp>
#include "AntTest.hpp"

IMPLEMENT_MAIN(AntTest)

void AntTest::onRun()
{
    // Basic setup
    Application::onRun();
    // add graphs for statistics
    setStats(false);
//	resetStats();
}


std::string AntTest::getHelpTextFile() const
{
    return RES_LOCATION + "ant-test-help.txt";
}

void AntTest::onEvent(sf::Event event, sf::RenderWindow& /*window*/)
{
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        default:
            break;
        case sf::Keyboard::S:
            getAppEnv().addAnimal(new AntSoldier(getCursorPositionInView(), createUid()));
            break;
        case sf::Keyboard::W:
            getAppEnv().addAnimal(new AntWorker(getCursorPositionInView(), createUid()));
            break;
        }

    }
}
/* To be used later
void AntTest::resetStats()
{
	Application::resetStats();
	addGraph(s::GENERAL, { s::WORKER_ANTS, s::SOLDIER_ANTS, s::TERMITES ,s::TEMPERATURE}, 0, 100);
	setActiveGraph(0);

}
*/

