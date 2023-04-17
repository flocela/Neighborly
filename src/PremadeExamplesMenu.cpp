#include "PremadeExamplesMenu.h"
#include <iostream>
#include <string>
#include "City_Grid.h"
#include "Simulator_Basic_B.h"
#include "SimulationComponents.h"
#include "Resident_UsingFunction.h"
#include "HappinessFunc_Falling.h"

using namespace std;
template<typename T>
std::unordered_set<T*> getSetOfPointers (std::vector<std::unique_ptr<T>>& ts)
{
    std::unordered_set<T*> pointers = {};
    for (auto& t : ts)
    {
        pointers.insert(t.get());
    }
    return pointers;
}

SimulationComponents PremadeExamplesMenu::userChoosesExample (const UI& ui)
{
    SimulationComponents components;


    int chosenCityAndResidentTypeCombo = ui.menu(
        "Which combination of city size and resident type? ",
        std::vector<std::string>{ 
            "simple with a small city", 
            "simple with a large city",
            "finicky residents with a small city",
            "finicky residents with a large city"},
            0,
            "Could not tell, which combo you wanted, will be using simple with a small city.");
    
    switch (chosenCityAndResidentTypeCombo)
    {
        case 0:
        {
            // 30 x 30 city with 900 houses. 
            // 360 Falling Resdients (Group 1)
            // 360 Falling Residents (Group 2)
            // happiness at one diversity = 50
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(30);

            // Only two groups. Group #1 and Group #2
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, _ordered_base_colors[ii-1]});
            }

            for (int ii=0; ii<360; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    15,   // allowed movement
                    60,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        50  // happiness value at one diversity
                    ),
                    "Falling Resident"
                ));
            }
            for (int jj=361; jj<720; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    15,
                    60,
                    std::make_unique<HappinessFunc_Falling>(
                        70, // happiness value with zero neighbors
                        95,
                        50),
                    "Falling Resident"
                ));
            }
            components.simulator = std::make_unique<Simulator_Basic_B>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30,
                20
            );

            components.numOfRuns = 20;
            
            break;
        }
        case 1:
        {
            // 120 x 120 city with 14,400 houses. 
            // 5760 Falling Resdients (Group 1)
            // 5760 Falling Residents (Group 2)
            // happiness at one diversity = 50
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(120);

            // Only two groups. Group #1 and Group #2
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, _ordered_base_colors[ii-1]});
            }

            for (int ii=0; ii<5760; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    30,   // allowed movement
                    60,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        50  // happiness value at one diversity
                    ),
                    "Falling Resident"
                ));
            }
            for (int jj=5761; jj<11520; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    30,
                    60,
                    std::make_unique<HappinessFunc_Falling>(
                        70, // happiness value with zero neighbors
                        95,
                        50),
                    "Falling Resident"
                ));
            }
            components.simulator = std::make_unique<Simulator_Basic_B>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30,
                20
            );

            components.numOfRuns = 30;
            
            break;
        }
        case 2:
        {
            // 30 x 30 city with 900 houses. 
            // 360 Falling Resdients (Group 1)
            // 360 Falling Residents (Group 2)
            // happiness at one diversity = 10
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(30);

            // Only two groups. Group #1 and Group #2
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, _ordered_base_colors[ii-1]});
            }

            for (int ii=0; ii<360; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    15,   // allowed movement
                    60,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        10  // happiness value at one diversity
                    ),
                    "Falling Resident"
                ));
            }
            for (int jj=361; jj<720; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    15,
                    60,
                    std::make_unique<HappinessFunc_Falling>(
                        70, // happiness value with zero neighbors
                        95,
                        10),
                    "Falling Resident"
                ));
            }
            components.simulator = std::make_unique<Simulator_Basic_B>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30,
                20
            );

            components.numOfRuns = 30;
            
            break;
        }
        case 3:
        {
            // 120 x 120 city with 14,400 houses. 
            // 5760 Falling Resdients (Group 1)
            // 5760 Falling Residents (Group 2)
            // happiness at one diversity = 10
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(120);

            // Only two groups. Group #1 and Group #2
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, _ordered_base_colors[ii-1]});
            }

            for (int ii=0; ii<5760; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    30,   // allowed movement
                    60,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        10  // happiness value at one diversity
                    ),
                    "Falling Resident"
                ));
            }
            for (int jj=5761; jj<11520; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    30,
                    60,
                    std::make_unique<HappinessFunc_Falling>(
                        70, // happiness value with zero neighbors
                        95,
                        10),
                    "Falling Resident"
                ));
            }
            components.simulator = std::make_unique<Simulator_Basic_B>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30,
                20
            );

            components.numOfRuns = 30;
            
            break;
        }
    }

    return components;
}