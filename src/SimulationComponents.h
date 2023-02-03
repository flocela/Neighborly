#ifndef SIMULATIONCOMPONENTS_H
#define SIMULATIONCOMPONENTS_H

#include <vector>
#include <memory>

#include "City.h"
#include "Color.h"
#include "Resident.h"
#include "Simulator.h"

struct SimulationComponents
{
    public:
        int numOfRuns = 0;
        std::unordered_map<int, BaseColor> baseColorsPerGroupid{};
        std::unique_ptr<City> city;
        std::vector<std::unique_ptr<Resident>> residents{};
        std::unique_ptr<Simulator> simulator;
        int randomSeed = 0;
};

#endif
