#ifndef USERCOMPONENTSGETTER_H
#define USERCOMPONENTSGETTER_H

#include "SimulationComponents.h"
#include <vector>
#include <memory>
#include "CityFactory.h"
#include "ResidentsFactory.h"
#include "UI_CMDLine.h"

class UserComponentsGetter
{
public:
    SimulationComponents askUserForComponents (
        const UI& ui,
        const std::vector<std::unique_ptr<CityFactory>>& cityFactories, //TODO sh0uld these by const cityFactories?
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentFactories, //TODO should these be const residentFactories?
        int maxNumOfHousesX,
        int maxNumOfHousesY,
        int maxNumOfResidentGroups,
        int maxNumOfRuns
    );
};

#endif