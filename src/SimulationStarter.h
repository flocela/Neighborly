#ifndef SIMULATION_STARTER_H
#define SIMULATION_STARTER_H

#include <fstream>
#include <memory>
#include <vector>
#include "City.h"
#include "Color.h"
#include "SimulationComponents.h"

// takes in a file and returns a SimulationComponents
class SimulationStarter
{
public:

    SimulationComponents createSimulationComponents (std::string inputTextFile);

private:
    std::unique_ptr<City> getCity(std::string cityString, std::vector<std::string> cityTypes);
    std::pair<int, BaseColor> returnBaseColor (std::ifstream& inputStream);
    void returnResidents (
        std::ifstream& inputStream, 
        std::vector<std::unique_ptr<Resident>>& residents
    );

    std::string leftTrim (std::string str);
};

#endif