#include "ComponentsFromUserGetter.h"

#include "CityMaker_CMDLine.h"
#include "CityState_Simple.h"
#include "RandSeedGetter.h"
#include "ResidentsMaker_CMDLine.h"
#include "Simulator_Basic_A.h"
#include "Simulator_Basic_B.h"
#include "Question_Double_II.h"
#include "Question_Int_II.h"
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

SimulationComponents ComponentsFromUserGetter::askUserForComponents (
    const UI& ui,
    const vector<unique_ptr<const CityFactory>>& cityFactories,
    const vector<unique_ptr<const ResidentsFactory>>& residentFactories,
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

    vector<BaseColor> baseColors;
    for (int ii=1; ii<=maxNumOfResidentGroups; ++ii) 
    {
        baseColors.push_back(_ordered_base_colors[ii-1]);
    }

    ResidentsMaker_CMDLine residentsMaker{};
    ResidentsGroupInfo resGroupInfo = 
        residentsMaker.makeResidents(
            ui,
            residentFactories,
            components.city->getNumOfHouses(),
            maxNumOfResidentGroups,
            baseColors,
            min(components.city->getWidth()/2, components.city->getHeight()/2));

    components.residents = move(resGroupInfo._residents);
    components.baseColorsPerGroupid = resGroupInfo._base_color_per_group_num;
    set<Resident*> residentPtrs = {};
    for (auto& resident: components.residents)
    {
        residentPtrs.insert(resident.get());
    }

    UINumOfRunsGetter runsGetter;
    components.numOfRuns = runsGetter.getNumOfRunsFromUser(ui, maxNumOfRuns);
    
        // Choose Simulator
    int chosenSimulator = ui.menu(
    "Which simulator would you like? In each run of Simulator A, all residents who are unhappy"
    " are given the opportunity to move to a house that will make them happier.\n"
    "In each run of Simulator B, a percentage of residents are randomly chosen and"
    " forced to move. From a given number of houses, they choose which one makes them happiest.\n",
    vector<string>{"Simulator A", "Simulator B"},
    1,
    "Could not tell which simulator you wanted, will choose Simulator B."
    );

    double percentageOfResidents = 20;
    int numberOfHousesToLookAt = components.city->getNumOfHouses()/5;
    if (chosenSimulator == 1) // Simulator B
    {
        Question_Double_II questionPercentOfResidentsThatMustMove  = Question_Double_II{
            0,
            0.0,
            100.0,
            20.0,
            "Simulator B chooses a percentage of all residents and forces them to move"
            " at each run. What should that percentage be? _",
            "percentage of residents moved per run"
        };
        percentageOfResidents = stod(ui.getAnswer(questionPercentOfResidentsThatMustMove));

        Question_Int_II questionNumberOfHouses = Question_Int_II{
            1,
            1,
            components.city->getNumOfHouses(),
            components.city->getNumOfHouses()/5,
            "The chosen residents will choose from a number of houses, and will choose which"
            " one makes them happiest. How many houses should they choose from? _",
            "number of housese to choose from"
        };
        numberOfHousesToLookAt = stoi(ui.getAnswer(questionNumberOfHouses));
    }

    if (chosenSimulator == 0)
    {
        components.simulator = make_unique<Simulator_Basic_A>(
            components.city.get(),
            getSetOfPointers(components.residents)
        );
    }
    else
    {
        components.simulator = make_unique<Simulator_Basic_B>(
            components.city.get(),
            getSetOfPointers(components.residents),
            percentageOfResidents,
            numberOfHousesToLookAt,
            make_unique<CityState_Simple>(components.city.get())
        );
    }

    return components;
}