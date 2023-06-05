#include "Printer_CMDLine.h"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

Printer_CMDLine::Printer_CMDLine (
    unordered_map<int, BaseColor> baseColorsPerGroupid,
    int maxNumofRuns,
    const City* cityPtr
):  _base_colors_per_groupid{baseColorsPerGroupid},
    _max_num_of_runs{maxNumofRuns},
    _city_ptr{cityPtr}
{}

void Printer_CMDLine::print(
    const RunMetrics* runMetrics,
    int run
) const
{   
    // get information from runMetrics
    unordered_map<const House*, const Resident*> residentsPerHouse =
        runMetrics->getResidentsPerHouse();
    unordered_map<int, int> numOfResidentsPerGroupId = runMetrics->getNumOfResidentsPerGroupId();
    unordered_map<int, int> numOfDiffNeighborsPerGroupId = runMetrics->getNumOfDiffNeighborsPerGroupId();
    unordered_map<int, double> happinessSumPerGroupId = runMetrics->getHappinessSumPerGroupId();
    unordered_map<int, const Resident*> residentExamplePerGroupId =
        runMetrics->getResidentExamplePerGroupId();

    // create a vector of group ids and sort the vector
    vector<int> groupIDs{};
    for (auto groupIDAndCount : numOfResidentsPerGroupId)
    {
        groupIDs.push_back(groupIDAndCount.first);
    }
    sort(groupIDs.begin(), groupIDs.end());

    // print header and inputs
    if (run == 0)
    {
        cout << endl << "Command Line Printer" << endl << endl;
        cout << "Inputs: " << endl;
        // print out resident information per group id and base colors.
        cout << "  Resident group info per groupId:" << endl;
        for (auto groupID : groupIDs)
        {
            const Resident* res = residentExamplePerGroupId[groupID];
            cout << "    Group id " << groupID << ":" << endl;
            cout << "      base color: " << _base_colors_per_groupid.at(groupID) <<
                    "      count: "<< numOfResidentsPerGroupId[groupID] << ", " <<
                    "      allowed movement: " << res->getAllowedMovementDistance() << ", " <<
                    "      happiness goal: " << res->getHappinessGoal() << "," << endl <<
                    "      " << res->toStrType() << endl;
        }
        cout << endl;
    }

    // print outputs
    cout << endl << "Outputs: " << endl;

    cout << "  Run: " << run << endl;

    for (int groupID : groupIDs)
    {   
        int numResidents = numOfResidentsPerGroupId[groupID];
        int numDiffNeighbors = numOfDiffNeighborsPerGroupId[groupID];
        double happinessSum = happinessSumPerGroupId[groupID];
        cout << "    Group id " << groupID << " diversity: " << 
        fixed << setprecision(2) << ((double)numDiffNeighbors/numResidents) << ", happiness sum: " <<
        (happinessSum/numResidents) << endl;
    }
    cout << endl;
    
    // Print out city map
    //if (run == 0 || run == _max_num_of_runs-1)
    {
        unordered_map<int, char> characterPerAddress{};

        for (auto pair : residentsPerHouse)
        {
            const House* house = pair.first;
            const Resident* resident = pair.second;
            int address = house->getAddress();
            if (resident->getHappiness() >= resident->getHappinessGoal()){
                characterPerAddress[address] = happyCharacters[resident->getGroupId()];
            }
            else
            {
                characterPerAddress[address] = resident->getGroupId() + 48;
            }
        }
        cout << "  City Map" << endl << "   key: " << endl;
        for (int groupID : groupIDs)
        {
            cout << "    GroupID " << groupID << ":: "
            << "happy: " << happyCharacters[groupID]
            << ", unhappy: " << groupID << endl;
        }
        cout << "    empty house: blank" << endl;
        cout << _city_ptr->toString(characterPerAddress) << endl;
        cout << endl;
    }
    

} 
