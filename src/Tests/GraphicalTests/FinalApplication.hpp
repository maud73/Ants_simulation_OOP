/*
 * POOSV 2020-21
 * Marco Antognini & Jamila Sam
 */

#ifndef INFOSV_FINAL_APPLICATION_HPP
#define INFOSV_FINAL_APPLICATION_HPP

#include <Application.hpp>
#include <Environment/Environment.hpp>


class FinalApplication : public Application
{
public:
    FinalApplication(int argc, char const** argv)
        : Application(argc, argv)
    {
    }
    virtual void onRun() override final;
    virtual void onSimulationStart() override final;
    virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
    virtual void resetStats() override final;
};

#endif // INFOSV_FINAL_APPLICATION_HPP
