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
): _city_printer{cityPrinter},
   _base_colors_per_groupid{baseColorsPerGroupid},
   _res_templates_per_group_id{resTemplatePerGroupId},
   _max_num_of_runs{maxNumofRuns},
   _seed_number{seedNumber},
   _simulator_name{simulatorName}
{}

void Printer_CmdLine::print (const RunMetrics* runMetrics) const
{   
    // Collect information from runMetrics.
    const ResPerHouse& residentsPerHouse = runMetrics->getResidentsPerHouse();
    const unordered_map<int, int>& numOfResidentsPerGroupId =
        runMetrics->getNumOfResidentsPerGroupId();
    const unordered_map<int, int>& numOfDiffNeighborsPerGroupId =
        runMetrics->getNumOfDiffNeighborsPerGroupId();
    const unordered_map<int, double>& happinessSumPerGroupId =
        runMetrics->getHappinessSumPerGroupId();
    int run = runMetrics->getRunNumber();

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
                 << _base_colors_per_groupid.at(groupID)
                 << "      count: "
                 << numOfResidentsPerGroupId.at(groupID) << ", "
                 << "      allowed movement: "
                 << _res_templates_per_group_id.at(groupID)->getAllowedMovementDistance() << ", "
                 << "      happiness goal: "
                 << _res_templates_per_group_id.at(groupID)->getHappinessGoal() << "," << endl
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
        // Create map of characters per address. It will assign a character to each 
        // address based on the resident's happiness.
        unordered_map<int, char> characterPerAddress{};
        for (auto pair : residentsPerHouse)
        {
            const House* house = pair.first;
            const Resident* resident = pair.second;
            int address = house->getAddress();
            // if resident's happiness is larger than happiness goal, assign the happiness
            // character for this group.
            if (resident->getHappiness() >= resident->getHappinessGoal()){
                characterPerAddress[address] = happyCharacters[resident->getGroupId()];
            }
            // else assign the groupId for this group.
            else
            {
                characterPerAddress[address] = resident->getGroupId() + 48; 
            }
        }
        // Print city map's key.
        cout << "    City Map" << endl << "      key: ";
        for (int groupID : groupIDs)
        {
            cout << "GroupID " << groupID << ":: "
                 << "happy: " << happyCharacters[groupID] << ", "
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
