/*
 * POOSV
 * 2020-21
 * Marco Antognini
 */

#include <Config.hpp>
#include <Environment/Environment.hpp>
#include <Environment/Anthill.hpp>
#include <Environment/Food.hpp>
#include "AnthillTest.hpp"

IMPLEMENT_MAIN(AnthillTest)

void AnthillTest::onRun()
{
    // Basic setup
    Application::onRun();
    // add graphs for statistics
    setStats(false);
//	resetStats();
    populate();
}


std::string AnthillTest::getHelpTextFile() const
{
    return RES_LOCATION + "anthill-test-help.txt";
}

void AnthillTest::populate()
{
    getAppEnv().reset(); // starts with an empty environment
    const auto x(getAppConfig().simulation_size);
    const auto y(x);
    ToricPosition pos(x/2,y/2);
    getAppEnv().addAnthill(new Anthill(pos));
}

void AnthillTest::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        getAppEnv().addFood(new Food(getCursorPositionInView(), 50));
    }
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        default:
        case sf::Keyboard::P:
            // UNCOMMENT WHEN THE METHOD IS CODED
            getAppEnv().togglePheromoneDisplay();
            break;
        case sf::Keyboard::H:
            getAppEnv().addAnthill(new Anthill(getCursorPositionInView()));
            break;
        }

    }
}
/* to be used later
void AnthillTest::resetStats()
{
	Application::resetStats();
	addGraph(s::GENERAL, { s::WORKER_ANTS, s::SOLDIER_ANTS, s::TERMITES ,s::TEMPERATURE}, 0, 100);
	const auto anthills_titles(getAppEnv().getAnthillsIds());
	addGraph(s::ANTHILLS, anthills_titles , 0, 1000);
	addGraph(s::FOOD,  { s::FOOD }, 0, 5000);
	setActiveGraph(0);
}
*/

