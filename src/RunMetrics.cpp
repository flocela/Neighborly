#include "RunMetrics.h"

using namespace std;

RunMetrics::RunMetrics (
    const City* cityPtr
): _city{cityPtr}
{
    for (const House* house : _city->getHouses())
    {
        _adj_houses[house] = _city->getHousesAdjacent(house->getAddress());
    }
}

void RunMetrics::updateMetrics(int run, unordered_map<const House*, const Resident*> residentsPerHouse)
{   (void)run; // TODO maybe remove run
    // clear previous runs' metrics
    _residents_per_house = residentsPerHouse;
    _num_of_residents_per_group_id = unordered_map<int, int>{};
    _num_of_diff_neighbors_per_group_id = unordered_map<int, int>{};
    _happiness_sum_per_group_id = unordered_map<int, double>{};
    _resident_example_per_group_id = unordered_map<int, const Resident*>{};
    
    // create house per resident map
    unordered_map<const Resident*, const House*> housePerResident{};
    for (auto houseAndResident : residentsPerHouse)
    {
        housePerResident.insert({houseAndResident.second, houseAndResident.first});
    }
    
    // TODO just use given residentsPerHouse to iterate through
    for (pair<const Resident*, const House*> ii : housePerResident)
    {
        const Resident* resident = ii.first;
        const House* house = ii.second;
        int residentGroupId = resident->getGroupId();
       
        if ( _resident_example_per_group_id.find(resident->getGroupId()) ==
            _resident_example_per_group_id.end() )
        {
            _resident_example_per_group_id[resident->getGroupId()] = resident;
        }

        unordered_set<const House*> housesAdjToRes = _adj_houses[house];

        int disparateNeighbors = 0;
        for (const House* adjacentHouse : housesAdjToRes)
        {
            // if adjacent house is not empty
            if (residentsPerHouse.find(adjacentHouse) != residentsPerHouse.end())
            {
                // adjacent resident's groupId
                int adj_res_groupId = (residentsPerHouse.at(adjacentHouse))->getGroupId();
                if (adj_res_groupId != residentGroupId)
                {
                    disparateNeighbors += 1;
                }
            }
        }
        
        if ( _num_of_diff_neighbors_per_group_id.find(residentGroupId) ==
             _num_of_diff_neighbors_per_group_id.end() )
        {
            _num_of_diff_neighbors_per_group_id[residentGroupId] = 0;
        }

        _num_of_diff_neighbors_per_group_id[residentGroupId] += disparateNeighbors;

        if (_happiness_sum_per_group_id.find(residentGroupId) == _happiness_sum_per_group_id.end())
        {
            _happiness_sum_per_group_id[residentGroupId] = 0;
        }

        _happiness_sum_per_group_id[residentGroupId] += resident->getHappiness();

        _num_of_residents_per_group_id[residentGroupId] += 1;
    }

}

unordered_map<const House*, const Resident*> RunMetrics::getResidentsPerHouse() const
{
    return _residents_per_house;
}

unordered_map<int, int> RunMetrics::getNumOfResidentsPerGroupId () const
{
    return _num_of_residents_per_group_id;
}

unordered_map<int, int> RunMetrics::getNumOfDiffNeighborsPerGroupId () const
{
    return _num_of_diff_neighbors_per_group_id;
}

unordered_map<int, double> RunMetrics::getHappinessSumPerGroupId () const
{
    return _happiness_sum_per_group_id;
}

unordered_map<int, const Resident*> RunMetrics::getResidentExamplePerGroupId () const
{
    return _resident_example_per_group_id;
}