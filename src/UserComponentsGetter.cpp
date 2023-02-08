#include "UserComponentsGetter.h"

#include "CityMaker_CMDLine.h"
#include "RandSeedGetter.h"
#include "ResidentsMaker_CMDLine.h"
#include "Simulator_Basic_A.h"
#include "UINumOfRunsGetter.h"

SimulationComponents UserComponentsGetter::askUserForComponents (
    const UI& ui,
    const std::vector<std::unique_ptr<const CityFactory>>& cityFactories,
    const std::vector<std::unique_ptr<const ResidentsFactory>>& residentFactories,
    int maxNumOfHousesX,
    int maxNumOfHousesY,
    int maxNumOfResidentGroups,
    int maxNumOfRuns
)
{
    SimulationComponents components{};
    RandSeedGetter randSeedGetter; 
    components.randomSeed = randSeedGetter.makeSeedForRand(ui);
    
    CityMaker_CMDLine cityMaker{ui};
    components.city = cityMaker.makeCity(cityFactories, maxNumOfHousesX, maxNumOfHousesY);

    std::vector<BaseColor> baseColors;
    auto iter = _colorrs_map.begin();
    for (int ii=1; ii<=maxNumOfResidentGroups; ++ii) 
    {
        baseColors.push_back((*iter).first);
        ++iter;
    }

    ResidentsMaker_CMDLine residentsMaker{};
    ResidentsGroupInfo resGroupInfo = 
        residentsMaker.makeResidents(
            ui,
            residentFactories,
            components.city->getNumOfHouses(),
            maxNumOfResidentGroups,
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
    components.numOfRuns = runsGetter.getNumOfRunsFromUser(ui, maxNumOfRuns);
    
    components.simulator = std::make_unique<Simulator_Basic_A>(components.city.get(), residentPtrs);

    return components;
}