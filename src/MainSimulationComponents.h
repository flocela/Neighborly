#ifndef MAINSIMULATIONCOMPONENTS_H
#define MAINSIMULATIONCOMPONENTS_H

#include "SimulationComponents.h"
#include <vector>
#include <memory>
#include "CityFactory.h"
#include "ResidentsFactory.h"
#include "UI_CMDLine.h"

class MainSimulationComponents
{
public:
    SimulationComponents askUserForComponents (
        const UI_CMDLine& ui,
        const std::vector<std::unique_ptr<CityFactory>>& cityFactories, //TODO sh0uld these by const cityFactories?
        const std::vector<std::unique_ptr<ResidentsFactory>>& residentFactories, //TODO should these be const residentFactories?
        int max_num_of_houses_x,
        int max_num_of_houses_y
    );

};

#endif