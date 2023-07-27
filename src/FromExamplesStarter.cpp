#include <memory>
#include <string>

#include "City_Grid.h"
#include "CityState_Simple.h"
#include "FromExamplesStarter.h"
#include "HappinessFunc_Falling.h"
#include "Resident_UsingFunction.h"
#include "SimulationComponents.h"
#include "Simulator_Basic_A.h"
#include "Simulator_Basic_B.h"

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

SimulationComponents FromExamplesStarter::createSimulationComponents (const UI& ui)
{
    SimulationComponents components;

    int chosenCityAndResidentTypeCombo = ui.menu(
        "\nWhich combination of simulator, city size, and resident types do you choose? ",
        std::vector<std::string>{ 
            "Simulator A with small city and regular residents", 
            "Simulator A with large city and regular residents",
            "Simulator A with small city and finicky residents", 
            "Simulator A with large city and finicky residents",
            "Simulator B with small city and regular residents", 
            "Simulator B with large city and regular residents",
            "Simulator B with small city and finicky residents", 
            "Simulator B with large city and finicky residents"},
            0,
            "Could not tell, which combo you wanted, will be using simulator a with a small city"
            " and simple residents.");
    
    switch (chosenCityAndResidentTypeCombo)
    {
        case 0:
        {
            // 30 x 30 city has 900 houses. 
            // 360 Falling Residents (Group 1)
            // 360 Falling Residents (Group 2)
            // SimulatorBasic_A
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(30);

            // Two groups means only two colors. Group #1 and Group #2.
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, _ordered_base_colors[ii-1]});
            }

            for (int ii=0; ii<360; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    15,  // allowed movement
                    80,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        50  // happiness value at one diversity
                    )
                ));
            }
            for (int jj=360; jj<720; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    15,
                    80,
                    std::make_unique<HappinessFunc_Falling>(
                        70,
                        95,
                        50)
                ));
            }

            components.residentTemplatePerGroupId
                .insert({1, components.residents[0]->getTemplate()});
            components.residentTemplatePerGroupId
                .insert({2, components.residents[360]->getTemplate()});

            components.simulator = std::make_unique<Simulator_Basic_A>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30, // percent of residents that are chosen to move each run
                20, // number of houses the residents can choose from
                make_unique<CityState_Simple>(components.city.get())
            );

            components.numOfRuns = 20;
            break; // end case 0

        }
        case 1:
        {
            // 120 x 120 city with 14,400 houses. 
            // 5760 Falling Resdients (Group 1)
            // 5760 Falling Residents (Group 2)
            // Simulator_Basic_A
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(120);

            // Two groups: Group #1 and Group #2
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, _ordered_base_colors[ii-1]});
            }

            for (int ii=0; ii<500; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    30,   // allowed movement
                    80,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        50  // happiness value at one diversity
                    )
                ));
            }
            for (int jj=5000; jj<10000; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    30,
                    80,
                    std::make_unique<HappinessFunc_Falling>(
                        70,
                        95,
                        50)
                ));
            }

            components.residentTemplatePerGroupId
                .insert({1, components.residents[0]->getTemplate()});
            components.residentTemplatePerGroupId
                .insert({2, components.residents[5760]->getTemplate()});

            components.simulator = std::make_unique<Simulator_Basic_A>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30, // percent of residents that are chosen to move each run
                20, // number of houses the residents can choose from
                make_unique<CityState_Simple>(components.city.get())
            );

            components.numOfRuns = 20;
            
            break; // end case 1
        }
        case 2:
        {
            // 30 x 30 city with 900 houses. 
            // 360 Falling Resdients (Group 1)
            // 360 Falling Residents (Group 2)
            // Simulator_Basic_A
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(30);

            // Two groups: Group #1 and Group #2
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
                    80,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        50  // happiness value at one diversity
                    )
                ));
            }
            for (int jj=360; jj<720; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    15,
                    80,
                    std::make_unique<HappinessFunc_Falling>(
                        70, 
                        95,
                        50)
                ));
            }

            components.residentTemplatePerGroupId
                .insert({1, components.residents[0]->getTemplate()});
            components.residentTemplatePerGroupId
                .insert({2, components.residents[360]->getTemplate()});

            components.simulator = std::make_unique<Simulator_Basic_A>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30, // percent of residents that are chosen to move each run
                20, // number of houses moving residents get to choose from
                move(make_unique<CityState_Simple>(components.city.get()))
            );

            components.numOfRuns = 20;
            
            break; // end case 2
        }
        case 3:
        {
            // 120 x 120 city with 14,400 houses. 
            // 5760 Falling Resdients (Group 1)
            // 5760 Falling Residents (Group 2)
            // Simulator_Basic_A
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(120);

            // Only two groups. Group #1 and Group #2
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, _ordered_base_colors[ii-1]});
            }

            for (int ii=0; ii<5000; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    30,   // allowed movement
                    80,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        100, // happiness value at zero diversity
                        0  // happiness value at one diversity
                    )
                ));
            }
            for (int jj=5000; jj<10000; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    30,
                    80,
                    std::make_unique<HappinessFunc_Falling>(
                        70,
                        100,
                        0)
                ));
            }

            components.residentTemplatePerGroupId
                .insert({1, components.residents[0]->getTemplate()});
            components.residentTemplatePerGroupId
                .insert({2, components.residents[5760]->getTemplate()});

            components.simulator = std::make_unique<Simulator_Basic_A>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30, // percent of residents that are chosen to move each run
                20, // number of houses moving residents get to choose from
                make_unique<CityState_Simple>(components.city.get())
            );

            components.numOfRuns = 20;
            
            break; // end case 3
        }
        case 4:
        {
            // 30 x 30 city has 900 houses. 
            // 360 Falling Residents (Group 1)
            // 360 Falling Residents (Group 2)
            // SimulatorBasic_B
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(30);

            // Two groups means only two colors. Group #1 and Group #2.
            for (int ii=1; ii<3; ++ii)
            {
                components.baseColorsPerGroupid.insert({ii, _ordered_base_colors[ii-1]});
            }

            for (int ii=0; ii<360; ++ii)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    ii,  // id
                    1,   // group number
                    15,  // allowed movement
                    80,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        50  // happiness value at one diversity
                    )
                ));
            }
            for (int jj=360; jj<720; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    15,
                    80,
                    std::make_unique<HappinessFunc_Falling>(
                        70,
                        95,
                        50)
                ));
            }

            components.residentTemplatePerGroupId
                .insert({1, components.residents[0]->getTemplate()});
            components.residentTemplatePerGroupId
                .insert({2, components.residents[360]->getTemplate()});

            components.simulator = std::make_unique<Simulator_Basic_B>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30, // percent of residents that are chosen to move each run
                20, // number of houses the residents can choose from
                make_unique<CityState_Simple>(components.city.get())
            );

            components.numOfRuns = 20;
            break; // end case 4

        }
        case 5:
        {
            // 120 x 120 city with 14,400 houses. 
            // 5760 Falling Resdients (Group 1)
            // 5760 Falling Residents (Group 2)
            // Simulator_Basic_B
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(120);

            // Two groups: Group #1 and Group #2
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
                    80,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        50  // happiness value at one diversity
                    )
                ));
            }
            for (int jj=5000; jj<10000; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    30,
                    80,
                    std::make_unique<HappinessFunc_Falling>(
                        70,
                        95,
                        50)
                ));
            }

            components.residentTemplatePerGroupId
                .insert({1, components.residents[0]->getTemplate()});
            components.residentTemplatePerGroupId
                .insert({2, components.residents[5760]->getTemplate()});

            components.simulator = std::make_unique<Simulator_Basic_B>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30, // percent of residents that are chosen to move each run
                20, // number of houses the residents can choose from
                make_unique<CityState_Simple>(components.city.get())
            );

            components.numOfRuns = 20;
            
            break; // end case 5
        }
        case 6:
        {
            // 30 x 30 city with 900 houses. 
            // 360 Falling Resdients (Group 1)
            // 360 Falling Residents (Group 2)
            // Simulator_Basic_B
            components.randomSeed = 0;
            
            components.city = std::make_unique<City_Grid>(30);

            // Two groups: Group #1 and Group #2
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
                    80,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        95, // happiness value at zero diversity
                        50  // happiness value at one diversity
                    )
                ));
            }
            for (int jj=360; jj<720; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    15,
                    80,
                    std::make_unique<HappinessFunc_Falling>(
                        70, 
                        95,
                        50)
                ));
            }

            components.residentTemplatePerGroupId
                .insert({1, components.residents[0]->getTemplate()});
            components.residentTemplatePerGroupId
                .insert({2, components.residents[360]->getTemplate()});

            components.simulator = std::make_unique<Simulator_Basic_B>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30, // percent of residents that are chosen to move each run
                20, // number of houses moving residents get to choose from
                move(make_unique<CityState_Simple>(components.city.get()))
            );

            components.numOfRuns = 20;
            
            break; // end case 6
        }
        case 7:
        {
            // 120 x 120 city with 14,400 houses. 
            // 5760 Falling Resdients (Group 1)
            // 5760 Falling Residents (Group 2)
            // Simulator_Basic_B
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
                    75,  // happiness goal
                    std::make_unique<HappinessFunc_Falling> (
                        70, // happiness value with zero neighbors
                        100, // happiness value at zero diversity
                        0  // happiness value at one diversity
                    )
                ));
            }
            for (int jj=5760; jj<11520; ++jj)
            {
                components.residents.push_back(std::make_unique<Resident_UsingFunction>(
                    jj,
                    2,
                    30,
                    75,
                    std::make_unique<HappinessFunc_Falling>(
                        70,
                        100,
                        0)
                ));
            }

            components.residentTemplatePerGroupId
                .insert({1, components.residents[0]->getTemplate()});
            components.residentTemplatePerGroupId
                .insert({2, components.residents[5760]->getTemplate()});

            components.simulator = std::make_unique<Simulator_Basic_B>(
                components.city.get(),
                getSetOfPointers(components.residents),
                30, // percent of residents that are chosen to move each run
                20, // number of houses moving residents get to choose from
                make_unique<CityState_Simple>(components.city.get())
            );

            components.numOfRuns = 20;
            
            break; // end case 7
        }
    }

    return components;
}