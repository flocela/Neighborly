#ifndef PREMADE_EXAMPLES_MENU_H
#define PREMADE_EXAMPLES_MENU_H

#include <vector>
#include <memory>
#include "Resident.h"
#include "City.h"
#include "UI_CMDLine.h"
#include "Simulator.h"
#include "SimulationComponents.h"


class PremadeExamplesMenu
{
public:
    SimulationComponents userChoosesExample (const UI& ui);
};

#endif