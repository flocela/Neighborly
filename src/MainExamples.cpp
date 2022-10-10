#include "MainExamples.h"

#include <string>
#include "City_Grid.h"
#include "Resident_StepDown.h"
#include "Simulator_Basic_A.h"
#include "SimulationComponents.h"

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

SimulationComponents MainExamples::userChoosesExample ()
{
    SimulationComponents components;
    int chosenExample = ui.menu(
        "Which example do you want to choose? ",
        std::vector<std::string>{ 
            "simple with a small city", 
            "simple with a large city",
            "finicky residents with a small city",
            "finicky residents with a large city"}
        );
    switch (chosenExample)
    {
        // 120 x 120 city with 14,400 houses. 
        // 200 StepDown (Blue)
        //     Unhappy if 80% or more neighbors are different from themselves.
        // 50  StepDown Residents (Red)
        //     Unhappy if 25% or more neighbors are different from themselves.
        case 1:
        {
            components.city = std::make_unique<City_Grid>(110);
            std::set<int> nums;
            nums.insert(1);
            nums.insert(2);
            components.groupNumbers = nums;
            for (int ii=0; ii<4000; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_StepDown>(
                    ii,  // id
                    1,   // group number
                    5,   // allowed movement
                    50,  // happiness goal
                    100, // happiness value at zero diversity
                    90,  // happiness value at one diverstiy
                    0.8  // diversity where drop happens
                ));
            }
            for (int jj=4001; jj<5000; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_StepDown>(
                    jj,
                    2,
                    20,
                    50,
                    100,
                    10,
                    0.25
                ));
            }
            components.simulator = std::make_unique<Simulator_Basic_A>(
                components.city.get(),
                getSetOfPointers(components.residents)
            );
            components.numOfRuns = 180;
            
            break;
        }
    }
    return components;
}