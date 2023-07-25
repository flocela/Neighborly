#ifndef FROM_EXAMPLES_STARTER_H
#define FROM_EXAMPLES_STARTER_H

#include <memory>
#include <vector>

#include "City.h"
#include "Resident.h"
#include "SimulationComponents.h"
#include "Simulator.h"
#include "UI_CmdLine.h"

// Asks the user which example to run.
class FromExamplesStarter
{
public:
    // Asks user which example to run. Then returns the SimulationComponents that 
    // can be used to generate the simulation.
    SimulationComponents createSimulationComponents (const UI& ui);
};

#endif