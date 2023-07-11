#ifndef FROM_QUESTIONS_STARTER_H
#define FROM_QUESTIONS_STARTER_H

#include <vector>
#include <memory>

#include "CityFactory.h"
#include "ResidentsFactory.h"
#include "SimulationComponents.h"

class FromQuestionsStarter
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