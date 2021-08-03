#ifndef MAIN_EXAMPLES_H
#define MAIN_EXAMPLES_H

#include <vector>
#include <memory>
#include "Resident.h"
#include "City.h"
#include "UI_CMDLine.h"
#include "Simulator.h"
#include "SimulationComponents.h"

class MainExamples
{
    public:
    // TODO in .cpp file these methods should raise an exception if userChoosesExample hasn't run yet!!!
        SimulationComponents userChoosesExample ();

    private:
        UI_CMDLine ui;
};

#endif