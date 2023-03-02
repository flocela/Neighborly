#ifndef COMPONENTSFROMUSERGETTER_H
#define COMPONENTSFROMUSERGETTER_H

#include <vector>
#include <memory>

#include "CityFactory.h"
#include "ResidentsFactory.h"
#include "SimulationComponents.h"

class ComponentsFromUserGetter
{
public:
    SimulationComponents askUserForComponents (
        const UI& ui,
        const std::vector<std::unique_ptr<const CityFactory>>& cityFactories, 
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentFactories,
        int maxNumOfHousesX,
        int maxNumOfHousesY,
        int maxNumOfResidentGroups,
        int maxNumOfRuns
    );
};

#endif