#include "SimulationStarter.h"

#include <fstream>
#include <iostream>
#include <set>
#include "City_Grid.h"
#include "Color.h"
#include "HappinessFunc_StepDown.h"
#include "Resident_UsingFunction.h"
#include "Simulator_Basic_A.h"

using namespace std;

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
        
        std::cout << "textfile city: " << components.city->getNumOfHouses() << endl;

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
        cout << "line 74: " << line << endl;
        if (line.find("<resident_group>") != string::npos)
        {
           returnResidents(inputStream, components.residents);
        }

        getline(inputStream, line);
        cout << "line 81: " << line << endl;
        if (line.find("<resident_group>") != string::npos)
        {   cout << "resident Group line 81" << endl;
            returnResidents(inputStream, components.residents);
        }

        // simulator
        getline(inputStream, line);
        cout << "line: " <<  line << endl;
        if (line.find("<simulator>") != string::npos)
        {   cout << "find <simulator>" << endl;
            string simulator = "";
            getline(inputStream, line);
            if (line.find("<name>") != string::npos)
            {   cout << "find name: " << endl;
                getline(inputStream, simulator);
                simulator = leftTrim(simulator);
                getline(inputStream, line);
            }
            if (simulator == "Simulator_Basic_A")
            {   cout << "Simulator Basic A makeing" << endl;
                components.simulator = std::make_unique<Simulator_Basic_A>(
                components.city.get(),
                getSetOfPointers(components.residents)
            );
            }
            getline(inputStream, line); // </simulator>
        }
        cout << "109: line: " << line << endl;

        // number of runs
        getline(inputStream, line);
        if (line.find("<num_of_runs>") != string::npos)
        {   cout << "numOf runs, inside: " <<endl;
            string numOfRuns = "";
            getline(inputStream, numOfRuns);
            numOfRuns = leftTrim(numOfRuns);
            getline(inputStream, line); // </num_of_runs>
            components.numOfRuns = stoi(numOfRuns);
        }

    }
    cout << "components.residents.size():  " << components.residents.size() << endl;
    cout << "components.simulator nullptr" << (components.simulator == nullptr) << endl;
    cout << "components. simulator: " << components.simulator->toString() << endl;
    cout << "components.runs: " << components.numOfRuns << endl;

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
    BaseColor c = _base_colors[leftTrim(baseColor)];
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
    {   cout << "start_id" <<endl;
        getline(inputStream, startId);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("<number_of>") != string::npos)
    {   cout << "numberOf" <<endl;
        getline(inputStream, numberOf);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("group_id") != string::npos)
    {   cout << "group_id" <<endl;
        getline(inputStream, groupId);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("<allowed_movement>") != string::npos)
    {   cout << "allowed_movement" <<endl;
        getline(inputStream, allowedMovement);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("<happiness_goal>") != string::npos)
    {   cout << "happiness_goal" <<endl;
        getline(inputStream, happinessGoal);
        getline(inputStream, line);
    }
    getline(inputStream, line);
    if (line.find("<resident_type>") != string::npos)
    {   cout << "resident_type" <<endl;
        getline(inputStream, residentType);
        residentType = leftTrim(residentType);
        getline(inputStream, line);
        cout <<"residentTYpe: " << residentType << endl;
    }
    if (residentType == "Resident_UsingFunction")
    {   cout << "Resident_UsingFunction" <<endl;
        string happinessFunction = "";
        getline(inputStream, line);
        if (line.find("<happiness_function>") != string::npos)
        {   cout << "happiness_function" <<endl;
            getline(inputStream, happinessFunction);
            happinessFunction = leftTrim(happinessFunction);
            getline(inputStream, line);
        }
        if (happinessFunction == "HappinessFunction_StepDown")
        {   cout << "HappinessFunction_StepDown" <<endl;
            string zeroNeighbors = "";
            string happinessAtZeroDiversity = "";
            string happinessAtOneDiversity = "";
            string diversityDropLocation = "";
            string name = "";
            getline(inputStream, line);
            if (line.find("zero_neighbors") != string::npos)
            {   cout << "zero_neighbors" <<endl;
                getline(inputStream, zeroNeighbors);
                getline(inputStream, line);
            }
            getline(inputStream, line);
            if (line.find("happiness_at_zero_diversity") != string::npos)
            {   cout << "happiness_at_zero_diversity" <<endl;
                getline(inputStream, happinessAtZeroDiversity);
                getline(inputStream, line);
            }
            getline(inputStream, line);
            if (line.find("happiness_at_one_diversity") != string::npos)
            {   cout << "happiness_at_one_diversity" <<endl;
                getline(inputStream, happinessAtOneDiversity);
                getline(inputStream, line);
            }
            getline(inputStream, line);
            if (line.find("diversity_drop_location") != string::npos)
            {   cout << "diversity_drop_location" <<endl;
                getline(inputStream, diversityDropLocation);
                getline(inputStream, line);
            }
            getline(inputStream, line);
            if (line.find("name") != string::npos)
            {   cout << "name" <<endl;
                getline(inputStream, name);
                getline(inputStream, line);
            }
        
            getline(inputStream, line); // </resident_group
            
            int firstID = stoi(startId);
            cout << "numberOf: " << numberOf << endl;
            for (int ii = 0; ii< stoi(numberOf); ++ii)
            {   
                residents.push_back(make_unique<Resident_UsingFunction> (
                    firstID + ii,
                    stoi(groupId),
                    stoi(allowedMovement),
                    stod(happinessGoal),
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
    }
}

string SimulationStarter::leftTrim (string str)
{
    size_t start = str.find_first_not_of(" ");
    return (start == std::string::npos) ? "" : str.substr(start);
}