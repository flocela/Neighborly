#ifndef SIMULATION_STARTER_H
#define SIMULATION_STARTER_H

#include <fstream>
#include <memory>
#include <vector>
#include "City.h"
#include "Color.h"
#include "SimulationComponents.h"
#include "Simulator_Basic_A.h"
#include "Simulator_Basic_B.h"

// takes in a file and returns a SimulationComponents
class SimulationStarter
{
public:

    SimulationComponents createSimulationComponents (std::string inputTextFile);

private:
    std::unique_ptr<City> getCity(std::string cityString, std::vector<std::string> cityTypes);
    std::pair<int, BaseColor> returnBaseColor (std::ifstream& inputStream);

    void populateResidents (
        std::ifstream& inputStream, 
        std::vector<std::unique_ptr<Resident>>& residents
    );

    std::unique_ptr<Simulator_Basic_A> returnSimulatorBasicA (
        std::ifstream& inputStream,
        const SimulationComponents& components
    );

    std::unique_ptr<Simulator_Basic_B> returnSimulatorBasicB (
        std::ifstream& inputStream,
        const SimulationComponents& components
    );

    void populateResidentsWithStepDownFunc (
        std::ifstream& inputStream,
        std::vector<std::unique_ptr<Resident>>& residents,
        int startId,
        int numberOfResidents,
        int groupId,
        double allowedMovement,
        double happinessGoal
    );
    
    void populateResidentsWithStepUpFunc (
        std::ifstream& inputStream,
        std::vector<std::unique_ptr<Resident>>& residents,
        int startId,
        int numberOfResidents,
        int groupId,
        double allowedMovement,
        double happinessGoal
    );

    void populateResidentsWithFallingFunc (
        std::ifstream& inputStream,
        std::vector<std::unique_ptr<Resident>>& residents,
        int startId,
        int numberOfResidents,
        int groupId,
        double allowedMovement,
        double happinessGoal
    );

    void populateResidentsWithRisingFunc (
        std::ifstream& inputStream,
        std::vector<std::unique_ptr<Resident>>& residents,
        int startId,
        int numberOfResidents,
        int groupId,
        double allowedMovement,
        double happinessGoal
    );

    void populateResidentsWithFlatFunc (
        std::ifstream& inputStream,
        std::vector<std::unique_ptr<Resident>>& residents,
        int startId,
        int numberOfResidents,
        int groupId,
        double allowedMovement,
        double happinessGoal
    );

    std::string leftTrim (std::string str);
};

#endif