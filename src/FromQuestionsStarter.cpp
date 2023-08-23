#include "CityMaker_CmdLine.h"
#include "CityState_Simple.h"
#include "FromQuestionsStarter.h"
#include "RandomSeedGetter.h"
#include "ResidentsMaker_CmdLine.h"
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

SimulationComponents FromQuestionsStarter::createSimulationComponents (
    const UI& ui,
    const vector<unique_ptr<const CityFactory>>& cityFactories,
    const vector<unique_ptr<const ResidentsFactory>>& residentFactories,
    int maxNumOfHousesX,
    int maxNumOfHousesY,
    int maxNumOfRuns
)
{
    // resultantComponents will be returned.
    // Create here, and add information to it before returning.
    SimulationComponents resultantComponents{};

    // group colors
    vector<BaseColor> baseColors;
    baseColors.push_back(_ordered_base_colors[0]);
    baseColors.push_back(_ordered_base_colors[1]);

    // Add random seed.
    resultantComponents.randomSeed = RandomSeedGetter::getSeedFromUser(ui);
    
    // Add city.
    CityMaker_CmdLine cityMaker{ui};
    resultantComponents.city = cityMaker.makeCity(cityFactories, maxNumOfHousesX, maxNumOfHousesY);

    // Create group info for residents.
    ResidentsMaker_CmdLine residentsMaker{};
    ResidentsGroupInfo resGroupInfo = residentsMaker.makeResidents(
        ui,
        residentFactories,
        resultantComponents.city->getNumOfHouses(),
        baseColors,
        min(resultantComponents.city->getWidth()/2, resultantComponents.city->getHeight()/2));

    // Add residents.
    resultantComponents.residents = move(resGroupInfo._residents);

    // Add resident type per group id.
    resultantComponents.residentTemplatePerGroupId
        = move(resGroupInfo._res_template_per_group_id);

    // Add group colors per resident.
    resultantComponents.baseColorsPerGroupid = resGroupInfo._base_color_per_group_num;

    // Add number of runs.
    resultantComponents.numOfRuns = UINumOfRunsGetter::getNumOfRunsFromUser(ui, maxNumOfRuns);
    
    // Add Simulator.
    SimulatorGetter simulatorGetter{
        resultantComponents.city.get(),
        getSetOfPointers(resultantComponents.residents)};
    resultantComponents.simulator = simulatorGetter.getSimulatorFromUser(ui);

    return resultantComponents;
}