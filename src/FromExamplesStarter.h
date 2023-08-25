#ifndef FROM_EXAMPLES_STARTER__H
#define FROM_EXAMPLES_STARTER__H

#include "SimulationComponents.h"
#include "UI.h"

// Asks the user which example to run.
class FromExamplesStarter
{

public:

    // Asks user which example to run. Then returns the SimulationComponents that 
    // can be used to generate the simulation.
    SimulationComponents createSimulationComponents (const UI& ui);
    
};

#endif