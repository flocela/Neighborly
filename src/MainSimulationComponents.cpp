#include "MainSimulationComponents.h"
#include "SimulationComponents.h"
#include "RandSeedGetter.h"
#include "CityMaker_CMDLine.h"
#include "ResidentsMaker_CMDLine.h"
#include "UINumOfRunsGetter.h"
#include "Simulator_Basic_A.h"

SimulationComponents MainSimulationComponents::askUserForComponents (
    const UI_CMDLine& ui,
    const std::vector<std::unique_ptr<CityFactory>>& cityFactories,
    const std::vector<std::unique_ptr<ResidentsFactory>>& residentFactories,
    int max_num_of_houses_x,
    int max_num_of_houses_y
)
{
    SimulationComponents components{};
    RandSeedGetter randSeedGetter; 
    components.randomSeed = randSeedGetter.makeSeedForRand(ui);
    
    CityMaker_CMDLine cityMaker{ui};
    components.city = cityMaker.makeCity(cityFactories, max_num_of_houses_x, max_num_of_houses_y);

    // Only two groups of residents. Group 1 and Group 2.
    std::vector<BaseColor> baseColors;
    auto iter = _colorrs_map.begin();
    for (int ii=1; ii<3; ++ii) 
    {
        baseColors.push_back((*iter).first);
        ++iter;
    }

    ResidentsMaker_CMDLine residentsMaker{ui};
    ResidentsGroupInfo resGroupInfo = 
        residentsMaker.makeResidents(
        residentFactories,
        components.city->getNumOfHouses(),
        2, // currenlty only allowing two groups
        baseColors,
        std::min(components.city->getWidth()/2, components.city->getHeight()/2));

    components.residents = std::move(resGroupInfo._residents);
    components.baseColorsPerGroupid = resGroupInfo._base_color_per_group_num;
    std::set<Resident*> residentPtrs = {};
    for (auto& resident: components.residents)
    {
        residentPtrs.insert(resident.get());
    }

    UINumOfRunsGetter runsGetter;
    components.numOfRuns = runsGetter.getNumOfRunsFromUser();
    
    components.simulator = std::make_unique<Simulator_Basic_A>(components.city.get(), residentPtrs);

    return components;
}