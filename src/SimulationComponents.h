#ifndef SIMULATIONCOMPONENTS_H
#define SIMULATIONCOMPONENTS_H

#include <memory>
#include <vector>
#include "City.h"
#include "Resident.h"
#include "Simulator.h"

struct SimulationComponents
{
    public:
        int numOfRuns;
        std::set<int> groupNumbers;
        std::unique_ptr<City> city;
        std::vector<std::unique_ptr<Resident>> residents;
        std::unique_ptr<Simulator> simulator;
};

#endif
