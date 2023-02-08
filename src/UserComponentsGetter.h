#ifndef USERCOMPONENTSGETTER_H
#define USERCOMPONENTSGETTER_H

#include <vector>
#include <memory>

#include "CityFactory.h"
#include "ResidentsFactory.h"
#include "SimulationComponents.h"

class UserComponentsGetter
{
public:
    SimulationComponents askUserForComponents (
        const UI& ui,
        const std::vector<std::unique_ptr<const CityFactory>>& cityFactories, 
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentFactories, //TODO should these be const residentFactories?
        int maxNumOfHousesX,
        int maxNumOfHousesY,
        int maxNumOfResidentGroups,
        int maxNumOfRuns
    );
};

#endif