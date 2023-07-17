#ifndef SIMULATIONCOMPONENTS_H
#define SIMULATIONCOMPONENTS_H

#include <vector>
#include <memory>

#include "City.h"
#include "Color.h"
#include "Resident.h"
#include "ResidentTemplate.h"
#include "Simulator.h"

// Used to construct SimulationComponents
struct SimulationComponents
{
public:
    int numOfRuns = 0;
    std::unordered_map<int, BaseColor> baseColorsPerGroupid{};
    std::unordered_map<int, std::unique_ptr<ResidentTemplate>> residentTemplatePerGroupId{};
    std::unique_ptr<City> city;
    std::vector<std::unique_ptr<Resident>> residents{};
    std::unique_ptr<Simulator> simulator;
    int randomSeed = 0;
   
};

#endif
