#include "SimulationStarter.h"

#include <fstream>
#include <iostream>
#include <set>
#include "City_Grid.h"
#include "Color.h"
#include "HappinessFunc_Falling.h"
#include "HappinessFunc_Flat.h"
#include "HappinessFunc_Rising.h"
#include "HappinessFunc_StepDown.h"
#include "HappinessFunc_StepUp.h"
#include "Resident_UsingFunction.h"
#include "Simulator_Basic_A.h"

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

SimulationComponents SimulationStarter::createSimulationComponents(string inputTextFile)
{
    SimulationComponents components;
    ifstream inputStream;
    inputStream.open(inputTextFile);
    if (inputStream.is_open())
    {
        string line = "";
        getline(inputStream, line);
        // city
        if (line.find("<city>") != string::npos)
        {   
            string cityType ="";
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
            returnResidents(inputStream, components.residents);
            }

            getline(inputStream, line);
        }
        
        // simulator
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
                components.simulator = std::make_unique<Simulator_Basic_A>(
                components.city.get(),
                getSetOfPointers(components.residents)
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

pair<int, BaseColor> SimulationStarter::returnBaseColor (ifstream& inputStream)
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

void SimulationStarter::returnResidents (
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
    if (residentType == "Resident_UsingFunction")
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
            returnResidentsWithStepDownFunc(
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
            returnResidentsWithStepUpFunc(
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
            returnResidentsWithFallingFunc(
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
            returnResidentsWithRisingFunc(
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
            returnResidentsWithFlatFunc(
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

void SimulationStarter::returnResidentsWithStepDownFunc (
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
    getline(inputStream, line);
    if (line.find("name") != string::npos)
    {   
        getline(inputStream, name);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_UsingFunction> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_StepDown>(
                stod(zeroNeighbors),
                stod(happinessAtZeroDiversity),
                stod(happinessAtOneDiversity),
                stod(diversityDropLocation)
            ),
            name
        ));
    }
}

void SimulationStarter::returnResidentsWithStepUpFunc (
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
    getline(inputStream, line);
    if (line.find("name") != string::npos)
    {   
        getline(inputStream, name);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_UsingFunction> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_StepUp>(
                stod(zeroNeighbors),
                stod(happinessAtZeroDiversity),
                stod(happinessAtOneDiversity),
                stod(diversityDropLocation)
            ),
            name
        ));
    }
}

void SimulationStarter::returnResidentsWithFallingFunc (
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
    if (line.find("name") != string::npos)
    {   
        getline(inputStream, name);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_UsingFunction> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Falling>(
                stod(zeroNeighbors),
                stod(happinessAtZeroDiversity),
                stod(happinessAtOneDiversity)
            ),
            name
        ));
    }
}

void SimulationStarter::returnResidentsWithRisingFunc (
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
    if (line.find("name") != string::npos)
    {   
        getline(inputStream, name);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_UsingFunction> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Rising>(
                stod(zeroNeighbors),
                stod(happinessAtZeroDiversity),
                stod(happinessAtOneDiversity)
            ),
            name
        ));
    }
}

void SimulationStarter::returnResidentsWithFlatFunc (
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
    string name = "";
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
    getline(inputStream, line);
    if (line.find("name") != string::npos)
    {   
        getline(inputStream, name);
        getline(inputStream, line);
    }

    getline(inputStream, line); // </resident_group
    
    
    int firstID = startId;
    for (int ii = 0; ii< numberOfResidents; ++ii)
    {   
        residents.push_back(make_unique<Resident_UsingFunction> (
            firstID + ii,
            groupId,
            allowedMovement,
            happinessGoal,
            make_unique<HappinessFunc_Flat>(
                stod(zeroNeighbors),
                stod(happinessValue)
            ),
            name
        ));
    }
}

string SimulationStarter::leftTrim (string str)
{
    size_t start = str.find_first_not_of(" ");
    return (start == std::string::npos) ? "" : str.substr(start);
}