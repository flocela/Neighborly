#include "MainExamples.h"
#include <iostream>
#include <string>
#include "City_Grid.h"
#include "Simulator_Basic_A.h"
#include "SimulationComponents.h"
#include "Resident_UsingFunction.h"
#include "HappinessFunc_StepDown.h"
template<typename T>
std::set<T*> getSetOfPointers (std::vector<std::unique_ptr<T>>& ts)
{
    std::set<T*> pointers = {};
    for (auto& t : ts)
    {
        pointers.insert(t.get());
    }
    return pointers;
}

SimulationComponents MainExamples::userChoosesExample (const UI& ui)
{
    SimulationComponents components;
    int chosenExample = ui.menu(
        "Which example do you want to choose? ",
        std::vector<std::string>{ 
            "simple with a small city", 
            "simple with a large city",
            "finicky residents with a small city",
            "finicky residents with a large city"},
            0,
            "Could not tell, which combo you wanted, will be using simple with a small city.");
    switch (chosenExample) // TODO only one type of example is listed in this switch statement, make more examples.
    {
        // 120 x 120 city with 14,400 houses. 
        // 200 StepDown (Blue)
        //     Unhappy if 80% or more neighbors are different from themselves.
        // 50  StepDown Residents (Red)
        //     Unhappy if 25% or more neighbors are different from themselves.
        case 0:
        {
            components.city = std::make_unique<City_Grid>(110);

            // Only two groups. Group #1 and Group #2
            auto iter = _colorrs_map.begin();
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, (*iter).first});
                ++iter;
            }

            for (int ii=0; ii<4000; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    10,   // allowed movement
                    80,  // happiness goal
                    std::make_unique<HappinessFunc_StepDown> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        70,  // happiness value at one diverstiy
                        0.25  // diversity where drop happens
                    ),
                    "Step Down Resident"
                ));
            }
            for (int jj=4001; jj<9000; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    40,
                    80,
                    std::make_unique<HappinessFunc_StepDown>(
                        70, // happiness value with zero neighbors
                        100,
                        50,
                        0.4),
                    "Step Down Resident"
                ));
            }
            components.simulator = std::make_unique<Simulator_Basic_A>(
                components.city.get(),
                getSetOfPointers(components.residents)
            );
            components.numOfRuns = 17;
            
            break;
        }
    }
    
    return components;
}