#ifndef PREMADE_EXAMPLES_MENU_H
#define PREMADE_EXAMPLES_MENU_H

#include <vector>
#include <memory>
#include "Resident.h"
#include "City.h"
#include "UI_CMDLine.h"
#include "Simulator.h"
#include "SimulationComponents.h"

// Asks the user which example to run.
class PremadeExamplesMenu
{
public:
    // Asks user which example to run. Then returns the SimulationComponents that 
    // can be used to generate the simulation.
    SimulationComponents userChoosesExample (const UI& ui);
};

#endif