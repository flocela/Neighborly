#ifndef COLLECTOR_BY_QUESTIONS__H
#define COLLECTOR_BY_QUESTIONS__H

#include "CityFactory.h"
#include "ResidentsFactory.h"
#include "SimulationComponents.h"

class CollectorByQuestions
{

public:

    SimulationComponents createSimulationComponents (
        const UI& ui,
        const std::vector<std::unique_ptr<const CityFactory>>& cityFactories, 
        const std::vector<std::unique_ptr<const ResidentsFactory>>& residentFactories,
        int maxNumOfHousesX,
        int maxNumOfHousesY,
        int maxNumOfRuns
    );
};

#endif