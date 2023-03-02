#include "Printer_CMDLine.h"

#include <algorithm>
#include <vector>

using namespace std;

Printer_CMDLine::Printer_CMDLine (
    unordered_map<int, BaseColor> baseColorsPerGroupid,
    int maxNumofRuns,
    City* cityPtr
):  _base_colors_per_groupid{baseColorsPerGroupid},
    _max_num_of_runs{maxNumofRuns},
    _city_ptr{cityPtr}
{
    for (const House* house : cityPtr->getHouses())
    {
        _adj_neighbors[house] = _city_ptr->getHousesAdjacent(house->getAddress());
    }
}

void Printer_CMDLine::print(
    unordered_map<const House*, const Resident*> residentPerHouse,
    int run
) const
{   cout << "Command Line Printer:" << endl;
    // create house per resident map
    unordered_map<const Resident*, const House*> housePerResident{};
    for (auto houseAndResident : residentPerHouse)
    {
        housePerResident.insert({houseAndResident.second, houseAndResident.first});
    }

    // Print out run number
    cout << "run: " << run << endl;

    // Collect data for diversity per group and happiness per group.
    // for each groupid, will need the number of residents in group,
    // the number of disparate neighbors,
    // and the happiness per group.
    unordered_map<int, int> numOfResidentsPerGroupId;
    unordered_map<int, int> numOfDiffNeighborsPerGroupId;
    unordered_map<int, double> happinessSumPerGroup;

    for (pair<const Resident*, const House*> ii : housePerResident)
    {
        const Resident* resident = ii.first;
        const House* house = ii.second;
        int residentGroupId = resident->getGroupId();
        set<const House*> housesAdjToRes = _city_ptr->getHousesAdjacent(house->getAddress());

        int disparateNeighbors = 0;
        for (const House* adjacentHouse : housesAdjToRes)
        {
            // if adjacent house is not empty
            if (residentPerHouse.find(adjacentHouse) != residentPerHouse.end())
            {
                // adjacent resident's groupId
                int adj_res_groupId = (residentPerHouse.at(adjacentHouse))->getGroupId();
                if (adj_res_groupId != residentGroupId)
                {
                    disparateNeighbors += 1;
                }
            }
        }
        if (numOfDiffNeighborsPerGroupId.find(residentGroupId) == numOfDiffNeighborsPerGroupId.end())
        {
            numOfDiffNeighborsPerGroupId[residentGroupId] = 0;
        }

        numOfDiffNeighborsPerGroupId[residentGroupId] += disparateNeighbors;

        if (happinessSumPerGroup.find(residentGroupId) == happinessSumPerGroup.end())
        {
            happinessSumPerGroup[residentGroupId] = 0;
        }

        happinessSumPerGroup[residentGroupId] += resident->getHappiness();

        numOfResidentsPerGroupId[residentGroupId] += 1;
    }

    // sort group ids
    
    vector<int> groupIDs{};
    for (auto groupIDAndCount : numOfResidentsPerGroupId)
    {
        groupIDs.push_back(groupIDAndCount.first);
    }
    sort(groupIDs.begin(), groupIDs.end());

    // Print out color groups
    cout << "Base Colors Per Group IDs:" << endl;

    for (int groupID: groupIDs)
    {
        cout << groupID << ":: " << _base_colors_per_groupid.at(groupID)<< endl;
    }

    cout << endl;

    // Print out Diversity and Happiness
    cout << "GroupID:: Diversity, Happiness: "<< endl;

    for (int groupID : groupIDs)
    {
        int numResidents = numOfResidentsPerGroupId[groupID];
        int numDiffNeighbors = numOfDiffNeighborsPerGroupId[groupID];
        cout << groupID << ":: " << (double)numDiffNeighbors/numResidents << 
            ", " << happinessSumPerGroup[groupID]/numOfResidentsPerGroupId[groupID] << endl;
    }
    cout << endl;
    
    // Print out city map
    unordered_map<int, char> characterPerAddress{};

    for (auto pair : residentPerHouse)
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
    
    cout << _city_ptr->toString(characterPerAddress) << endl;
    cout << endl;
    

} 
