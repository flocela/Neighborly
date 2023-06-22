#include "ComponentsGetter.h"

#include "CityMaker_CMDLine.h"
#include "CityState_Simple.h"
#include "RandomSeedGetter.h"
#include "ResidentsMaker_CMDLine.h"
#include "Simulator_Basic_A.h"
#include "Simulator_Basic_B.h"
#include "SimulatorGetter.h"
#include "UINumOfRunsGetter.h"

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

SimulationComponents ComponentsGetter::askUserForComponents (
    const UI& ui,
    const vector<unique_ptr<const CityFactory>>& cityFactories,
    const vector<unique_ptr<const ResidentsFactory>>& residentFactories,
    int maxNumOfHousesX,
    int maxNumOfHousesY,
    int maxNumOfRuns
)
{
    // Simulation Components. Need to add information to this container.
    SimulationComponents resultantComponents{};

    // group colors
    vector<BaseColor> baseColors;
    baseColors.push_back(_ordered_base_colors[0]);
    baseColors.push_back(_ordered_base_colors[1]);

    // add random seed
    resultantComponents.randomSeed = RandomSeedGetter::getSeedFromUser(ui);
    
    // add city
    CityMaker_CMDLine cityMaker{ui};
    resultantComponents.city = cityMaker.makeCity(cityFactories, maxNumOfHousesX, maxNumOfHousesY);

    // create group info for residents
    ResidentsMaker_CMDLine residentsMaker{};
    ResidentsGroupInfo resGroupInfo = residentsMaker.makeResidents(
        ui,
        residentFactories,
        resultantComponents.city->getNumOfHouses(),
        baseColors,
        min(resultantComponents.city->getWidth()/2, resultantComponents.city->getHeight()/2));

    // add residents
    resultantComponents.residents = move(resGroupInfo._residents);

    // add group colors per resident
    resultantComponents.baseColorsPerGroupid = resGroupInfo._base_color_per_group_num;

    // add number of runs.
    resultantComponents.numOfRuns = UINumOfRunsGetter::getNumOfRunsFromUser(ui, maxNumOfRuns);
    
    // add Simulator
    SimulatorGetter simulatorGetter{
        resultantComponents.city.get(),
        getSetOfPointers(resultantComponents.residents)};
    resultantComponents.simulator = simulatorGetter.getSimulatorFromUser(ui);

    return resultantComponents;
}