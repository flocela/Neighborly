#ifndef COLLECTOR_BY_EXAMPLES__H
#define COLLECTOR_BY_EXAMPLES__H

#include "SimulationComponents.h"
#include "UI.h"

// Asks the user which example to run.
class CollectorByExamples
{

public:

    // Asks user which example to run. Then returns the SimulationComponents that 
    // can be used to generate the simulation.
    SimulationComponents createSimulationComponents (const UI& ui);
    
};

#endif