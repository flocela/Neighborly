#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Printer_CmdLine.h"

using namespace std;

Printer_CmdLine::Printer_CmdLine (
    const CityPrinter& cityPrinter,
    const unordered_map<int, BaseColor>& baseColorsPerGroupid,
    const std::unordered_map<int, unique_ptr<const ResidentTemplate>>& resTemplatePerGroupId,
    int maxNumofRuns,
    int seedNumber,
    string simulatorName
): 
    _city_printer{cityPrinter},
    _base_colors_per_groupid{baseColorsPerGroupid},
    _res_templates_per_group_id{resTemplatePerGroupId},
    _max_num_of_runs{maxNumofRuns},
    _seed_number{seedNumber},
    _simulator_name{simulatorName}
{}

void Printer_CmdLine::print (const RunMetrics* runMetrics) const
{   
    // Collect information from @runMetrics.
    int run = runMetrics->getRunNumber();
    const ResPerHouse& residentsPerHouse = runMetrics->getResidentsPerHouse();
    const unordered_map<int, int>& numOfResidentsPerGroupId =
        runMetrics->getNumOfResidentsPerGroupId();

    // The number of different neighbors per group is found by taking the sum of disparate
    // neighbors for each resident in the group.
    const unordered_map<int, int>& numOfDiffNeighborsPerGroupId =
        runMetrics->getNumOfDiffNeighborsPerGroupId();
    
    // Happiness sum per group id is a sum per group id. Take each resident in the
    // group and add their happiness to the group's happiness sum.
    const unordered_map<int, double>& happinessSumPerGroupId =
        runMetrics->getHappinessSumPerGroupId();
    
    // Create a vector of group ids and sort the vector
    vector<int> groupIDs{};
    for (auto groupIDAndCount : numOfResidentsPerGroupId)
    {
        groupIDs.push_back(groupIDAndCount.first);
    }
    sort(groupIDs.begin(), groupIDs.end());

    // Print header and inputs
    if (run == 0)
    {
        cout << endl << "Command Line Printer" << endl << endl;
        cout << "Inputs: " << endl;

        // Print out resident information per group id and base colors.
        cout << "  Resident group info per groupId:" << endl;
        for (auto groupID : groupIDs)
        {
            cout << "    Group id " << groupID << ":" << endl;
            cout << "      base color: "
                 << _base_colors_per_groupid.at(groupID) << ", "
                 << "      count: "
                 << numOfResidentsPerGroupId.at(groupID) << ", "
                 << "      allowed movement: "
                 << _res_templates_per_group_id.at(groupID)->getAllowedMovementDistance() << ", "
                 << "      happiness goal: "
                 << _res_templates_per_group_id.at(groupID)->getHappinessGoal() << endl
                 << "      " << _res_templates_per_group_id.at(groupID)->getType() << endl;
        }

        cout << "  Simulator: " << _simulator_name << endl;
        cout << "  Seed for random number generator: " << _seed_number << endl;
        cout << endl;
    }

    // Print run outputs.
    cout << endl << "Outputs: " << endl;

    cout << "  Run: " << run << endl;
    cout << fixed << setprecision(2);

    for (int groupID : groupIDs)
    {   
        int numResidents = numOfResidentsPerGroupId.at(groupID);
        double numDiffNeighbors = (double)numOfDiffNeighborsPerGroupId.at(groupID);
        double happinessSum = happinessSumPerGroupId.at(groupID);
        cout << "    Group id " << groupID << " "
             << "diversity: " << (numDiffNeighbors/numResidents) << ", "
             << "happiness sum: " << (happinessSum/numResidents) << endl;
    }
    cout << endl;
    
    // Print city map if on first or last run.
    if (run == 0 || run == _max_num_of_runs-1)
    {
        // Create map of characters per address. If the address is empty, then the
        // character is an empty space. If the address has a resident, then the
        // corresponding character depends on the resident's group id and happiness. If the
        // resident's happiness is less than it's happiness goal, then the 
        // address's corresponding character is the resident's group id . If the resident's
        // happiness is greater or equal to the resident's happiness goal, then the
        // corresponding character is group's happiness character (from _happy_characers vector).
        unordered_map<int, char> characterPerAddress{};
        for (auto houseAndRes : residentsPerHouse)
        {
            int residentGroupId = houseAndRes.second->getGroupId();
            double residentsHappiness = houseAndRes.second->getHappiness();
            double residentsHappinessGoal = houseAndRes.second->getHappinessGoal();
            int address = houseAndRes.first->getAddress();
            if (residentsHappiness >= residentsHappinessGoal){
                characterPerAddress[address] = _happy_characters[residentGroupId];
            }
            else
            {
                // ASCII numbers are offset by 48.
                characterPerAddress[address] = residentGroupId + 48;
            }
        }
        // Print city map's key.
        cout << "    City Map" << endl << "      key: ";
        for (int groupID : groupIDs)
        {
            cout << "GroupID " << groupID << ":: "
                 << "happy: " << _happy_characters[groupID] << ", "
                 << "unhappy: " << groupID << endl << "           ";
        }
        cout << "empty house: -" << endl;

        // Use city printer to print out city map (residents and houses).
        cout << _city_printer.print(characterPerAddress) << endl;
        cout << endl;
    }
}

void Printer_CmdLine::lastPrint () {
    cout << "End of Simulation" << endl;
}
