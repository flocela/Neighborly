#include <iostream>
#include <fstream>
#include "City_Grid.h"
#include "CityState_Simple.h"
#include "Color.h"
#include "FromFileStarter.h"
#include "HappinessFunc_Falling.h"
#include "HappinessFunc_Flat.h"
#include "HappinessFunc_Rising.h"
#include "HappinessFunc_StepDown.h"
#include "HappinessFunc_StepUp.h"
#include "Resident_Customizable.h"

using namespace std;

template<typename T>
std::unordered_set<T*> getSetOfPointers (const std::vector<std::unique_ptr<T>>& ts)
{
    std::unordered_set<T*> pointers = {};
    for (auto& t : ts)
    {
        pointers.insert(t.get());
    }
    return pointers;
}

SimulationComponents FromFileStarter::createSimulationComponents(string inputTextFile)
{
    SimulationComponents components;
    ifstream inputStream;
    inputStream.open(inputTextFile);
    if (inputStream.is_open())
    {   
        // seed for random number generator.
        string line = "";
        getline(inputStream, line);
        if (line.find("<random_number>") != string::npos)
        {
            string randNum = "";
            getline(inputStream, randNum);
            components.randomSeed = stoi(randNum);
            getline(inputStream, line);      
        }

        // city
        getline(inputStream, line);
        if (line.find("<city>") != string::npos)
        {   
            string cityType = "";
            getline(inputStream, line);
        
            if (line.find("<type>") != string::npos)
            {   
                getline(inputStream, cityType);
                getline(inputStream, line);
            }
            if (cityType.find("City_Grid") != string::npos)
            {   
                string width = "";
                getline(inputStream, line);
                if (line.find("<width>") != string::npos)
                {   
                    getline(inputStream, width);
                    getline(inputStream, line);
                }
                
                components.city = std::make_unique<City_Grid>(stoi(width));
            }
            getline(inputStream, line); // </city>
        }

        // base color per group
        getline(inputStream, line);
        if (line.find("base_color_per_group") != string::npos)
        {   
            components.baseColorsPerGroupid.insert(returnBaseColor(inputStream));
            components.baseColorsPerGroupid.insert(returnBaseColor(inputStream));
            getline(inputStream, line); // </base_color_per_group>
        }
        
        // residents
        getline(inputStream, line);
        while (line.find("<resident_group") != string::npos)
        {
            if (line.find("<resident_group>") != string::npos)
            {
                populateResidents(inputStream, components.residents);

                // resident types per group id
                 const unique_ptr<Resident>& lastResident = components.residents.back();
                components.residentTemplatePerGroupId
                    .insert({lastResident->getGroupId(), lastResident->getTemplate()});
            }

            getline(inputStream, line);
        }
        
        if (line.find("<simulator>") != string::npos)
        {   
            string simulator = "";
            getline(inputStream, line);
            if (line.find("<name>") != string::npos)
            {   
                getline(inputStream, simulator);
                simulator = leftTrim(simulator);
                getline(inputStream, line);
            }
            if (simulator == "Simulator_Basic_A")
            {   
                components.simulator = returnSimulatorBasicA(
                    inputStream,
                    components
                );
            }
            else if (simulator == "Simulator_Basic_B")
            {
                components.simulator = returnSimulatorBasicB(
                    inputStream,
                    components
                );
            }
            getline(inputStream, line); // </simulator>
        }

        // number of runs
        getline(inputStream, line);
        if (line.find("<num_of_runs>") != string::npos)
        {   
            string numOfRuns = "";
            getline(inputStream, numOfRuns);
            numOfRuns = leftTrim(numOfRuns);
            getline(inputStream, line); // </num_of_runs>
            components.numOfRuns = stoi(numOfRuns);
        }

    }

    return components;
}

std::unique_ptr<Simulator_Basic_A> FromFileStarter::returnSimulatorBasicA (
    std::ifstream& inputStream,
    const SimulationComponents& components
)
{
    string line = "";
    string percentResidentsToMove = "";
    string numOfTries = "";

    getline(inputStream, line);
    if (line.find("percent_residents_to_move") != string::npos)
    {
        getline(inputStream, percentResidentsToMove);
        getline(inputStream, line);
    }

    getline(inputStream, line);
    if (line.find("num_of_tries") != string::npos)
    {
        getline(inputStream, numOfTries);
        getline(inputStream, line);
    }
    return std::make_unique<Simulator_Basic_A>(
            components.city.get(),
            getSetOfPointers(components.residents),
            stod(percentResidentsToMove),
            stoi(numOfTries),
            make_unique<CityState_Simple>(components.city.get())
    );
}

std::unique_ptr<Simulator_Basic_B> FromFileStarter::returnSimulatorBasicB (
    std::ifstream& inputStream,
    const SimulationComponents& components
)
{
    string line = "";
    string percentResidentsToMove = "";
    string numOfTries = "";
    getline(inputStream, line);
    if (line.find("percent_residents_to_move") != string::npos)
    {
        getline(inputStream, percentResidentsToMove);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("num_of_tries") != string::npos)
    {
        getline(inputStream, numOfTries);
        getline(inputStream, line);
    }
    return std::make_unique<Simulator_Basic_B>(
            components.city.get(),
            getSetOfPointers(components.residents),
            stod(percentResidentsToMove),
            stoi(numOfTries),
            make_unique<CityState_Simple>(components.city.get())
    );
}

pair<int, BaseColor> FromFileStarter::returnBaseColor (ifstream& inputStream)
{
    string groupId = "";
    string baseColor = "";
    string line = "";
    getline(inputStream, line);
    if (line.find("group") != string::npos)
    {  
        getline(inputStream, line);
        if (line.find("group_id") != string::npos)
        {   
            getline(inputStream, groupId);
            getline(inputStream, line);
        }
        getline(inputStream, line);
        if (line.find("base_color") != string::npos)
        {   
            getline(inputStream, baseColor);
            getline(inputStream, line);
        }
        getline(inputStream, line); // "</group>"
    }
    string trim = leftTrim(baseColor);
    BaseColor c = _base_colors[trim];
    return {stoi(groupId), c};
}

void FromFileStarter::populateResidents (
    ifstream& inputStream,
    vector<unique_ptr<Resident>>& residents
)
{   
    string line = "";
    string startId = "";
    string numberOf = "";
    string groupId = "";
    string allowedMovement = "";
    string happinessGoal = "";
    string residentType = "";
    getline(inputStream, line);
    if (line.find("<start_id>") != string::npos)
    {   
        getline(inputStream, startId);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("<number_of>") != string::npos)
    {  
        getline(inputStream, numberOf);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("group_id") != string::npos)
    {   
        getline(inputStream, groupId);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("<allowed_movement>") != string::npos)
    {   
        getline(inputStream, allowedMovement);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("<happiness_goal>") != string::npos)
    {  
        getline(inputStream, happinessGoal);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("<resident_type>") != string::npos)
    {   
        getline(inputStream, residentType);
        residentType = leftTrim(residentType);
        getline(inputStream, line);
    }
    if (residentType == "Resident_Customizable")
    {  
        string happinessFunction = "";
        getline(inputStream, line);
        if (line.find("<happiness_function>") != string::npos)
        {   
            getline(inputStream, happinessFunction);
            happinessFunction = leftTrim(happinessFunction);
            getline(inputStream, line);
        }
        if (happinessFunction == "HappinessFunction_StepDown")
        {   
            populateResidentsWithStepDownFunc(
                inputStream,
                residents,
                stoi(startId),
                stoi(numberOf),
                stoi(groupId),
                stod(allowedMovement),
                stod(happinessGoal));
        }
        if (happinessFunction == "HappinessFunction_StepUp")
        {   
            populateResidentsWithStepUpFunc(
                inputStream,
                residents,
                stoi(startId),
                stoi(numberOf),
                stoi(groupId),
                stod(allowedMovement),
                stod(happinessGoal));
        }
        if (happinessFunction == "HappinessFunction_Falling")
        {
            populateResidentsWithFallingFunc(
                inputStream,
                residents,
                stoi(startId),
                stoi(numberOf),
                stoi(groupId),
                stod(allowedMovement),
                stod(happinessGoal));
        }
        if (happinessFunction == "HappinessFunction_Rising")
        {
            populateResidentsWithRisingFunc(
                inputStream,
                residents,
                stoi(startId),
                stoi(numberOf),
                stoi(groupId),
                stod(allowedMovement),
                stod(happinessGoal));
        }
        if (happinessFunction == "HappinessFunction_Flat")
        {   
            populateResidentsWithFlatFunc(
                inputStream,
                residents,
                stoi(startId),
                stoi(numberOf),
                stoi(groupId),
                stod(allowedMovement),
                stod(happinessGoal));
        }
    }
}

void FromFileStarter::populateResidentsWithStepDownFunc (
    std::ifstream& inputStream,
        std::vector<std::unique_ptr<Resident>>& residents,
        int startId,
        int numberOfResidents,
        int groupId,
        double allowedMovement,
        double happinessGoal
)
{   
    string line = "";
    string zeroNeighbors = "";
    string happinessAtZeroDiversity = "";
    string happinessAtOneDiversity = "";
    string diversityDropLocation = "";
    string name = "";
    getline(inputStream, line);
    if (line.find("zero_neighbors") != string::npos)
    {   
        getline(inputStream, zeroNeighbors);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_at_zero_diversity") != string::npos)
    {  
        getline(inputStream, happinessAtZeroDiversity);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_at_one_diversity") != string::npos)
    {   
        getline(inputStream, happinessAtOneDiversity);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("diversity_drop_location") != string::npos)
    { 
        getline(inputStream, diversityDropLocation);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_Customizable> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_StepDown>(
                stod(zeroNeighbors),
                stod(happinessAtZeroDiversity),
                stod(happinessAtOneDiversity),
                stod(diversityDropLocation)
            )
        ));
    }
}

void FromFileStarter::populateResidentsWithStepUpFunc (
    std::ifstream& inputStream,
        std::vector<std::unique_ptr<Resident>>& residents,
        int startId,
        int numberOfResidents,
        int groupId,
        double allowedMovement,
        double happinessGoal
)
{   
    string line = "";
    string zeroNeighbors = "";
    string happinessAtZeroDiversity = "";
    string happinessAtOneDiversity = "";
    string diversityDropLocation = "";
    getline(inputStream, line);
    if (line.find("zero_neighbors") != string::npos)
    {   
        getline(inputStream, zeroNeighbors);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_at_zero_diversity") != string::npos)
    {  
        getline(inputStream, happinessAtZeroDiversity);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_at_one_diversity") != string::npos)
    {   
        getline(inputStream, happinessAtOneDiversity);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("diversity_drop_location") != string::npos)
    { 
        getline(inputStream, diversityDropLocation);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_Customizable> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_StepUp>(
                stod(zeroNeighbors),
                stod(happinessAtZeroDiversity),
                stod(happinessAtOneDiversity),
                stod(diversityDropLocation)
            )
        ));
    }
}

void FromFileStarter::populateResidentsWithFallingFunc (
    std::ifstream& inputStream,
    std::vector<std::unique_ptr<Resident>>& residents,
    int startId,
    int numberOfResidents,
    int groupId,
    double allowedMovement,
    double happinessGoal
)
{   
    string line = "";
    string zeroNeighbors = "";
    string happinessAtZeroDiversity = "";
    string happinessAtOneDiversity = "";
    getline(inputStream, line);
    if (line.find("zero_neighbors") != string::npos)
    {   
        getline(inputStream, zeroNeighbors);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_at_zero_diversity") != string::npos)
    {  
        getline(inputStream, happinessAtZeroDiversity);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_at_one_diversity") != string::npos)
    {   
        getline(inputStream, happinessAtOneDiversity);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_Customizable> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Falling>(
                stod(zeroNeighbors),
                stod(happinessAtZeroDiversity),
                stod(happinessAtOneDiversity)
            )
        ));
    }
}

void FromFileStarter::populateResidentsWithRisingFunc (
    std::ifstream& inputStream,
    std::vector<std::unique_ptr<Resident>>& residents,
    int startId,
    int numberOfResidents,
    int groupId,
    double allowedMovement,
    double happinessGoal
)
{   
    string line = "";
    string zeroNeighbors = "";
    string happinessAtZeroDiversity = "";
    string happinessAtOneDiversity = "";
    getline(inputStream, line);
    if (line.find("zero_neighbors") != string::npos)
    {   
        getline(inputStream, zeroNeighbors);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_at_zero_diversity") != string::npos)
    {  
        getline(inputStream, happinessAtZeroDiversity);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_at_one_diversity") != string::npos)
    {   
        getline(inputStream, happinessAtOneDiversity);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_Customizable> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Rising>(
                stod(zeroNeighbors),
                stod(happinessAtZeroDiversity),
                stod(happinessAtOneDiversity)
            )
        ));
    }
}

void FromFileStarter::populateResidentsWithFlatFunc (
    std::ifstream& inputStream,
    std::vector<std::unique_ptr<Resident>>& residents,
    int startId,
    int numberOfResidents,
    int groupId,
    double allowedMovement,
    double happinessGoal
)
{   string line = "";
    string zeroNeighbors = "";
    string happinessValue = "";
    getline(inputStream, line);
    if (line.find("zero_neighbors") != string::npos)
    {   
        getline(inputStream, zeroNeighbors);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("happiness_value") != string::npos)
    {  
        getline(inputStream, happinessValue);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_Customizable> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Flat>(
                stod(zeroNeighbors),
                stod(happinessValue)
            )
        ));
    }
}

string FromFileStarter::leftTrim (string str)
{
    size_t start = str.find_first_not_of(" ");
    return (start == std::string::npos) ? "" : str.substr(start);
}