#ifndef COMPONENTSGETTER_H
#define COMPONENTSGETTER_H

#include <vector>
#include <memory>

#include "CityFactory.h"
#include "ResidentsFactory.h"
#include "SimulationComponents.h"

class ComponentsGetter
{
public:
    SimulationComponents askUserForComponents (
        const UI& ui,
        const std::vector<std::unique_ptr<const CityFactory>>& cityFactories, 
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentFactories,
        int maxNumOfHousesX,
        int maxNumOfHousesY,
        int maxNumOfRuns
    );
};

#endif