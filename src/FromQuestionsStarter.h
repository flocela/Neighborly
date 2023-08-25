#ifndef FROM_QUESTIONS_STARTER__H
#define FROM_QUESTIONS_STARTER__H

#include "CityFactory.h"
#include "ResidentsFactory.h"
#include "SimulationComponents.h"

class FromQuestionsStarter
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