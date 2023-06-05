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

    
    
    for (pair<const House*, const Resident*> houseThenResident : residentsPerHouse)
    {
        const House* house = houseThenResident.first;
        const Resident* resident = houseThenResident.second;
        int residentGroupId = resident->getGroupId();
        unordered_set<const House*> housesAdjToRes = _adj_houses[house];
       
        // populate _resident_example_per_group_id
        if ( _resident_example_per_group_id.find(resident->getGroupId()) ==
            _resident_example_per_group_id.end() )
        {
            _resident_example_per_group_id[resident->getGroupId()] = resident;
        }

        // number of neighbors that have a different groupId than resident
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
        
        // add number of disparate neighbors to sum of different neighbors for this group's id
        if ( _num_of_diff_neighbors_per_group_id.find(residentGroupId) ==
             _num_of_diff_neighbors_per_group_id.end() )
        {
            _num_of_diff_neighbors_per_group_id[residentGroupId] = 0;
        }

        _num_of_diff_neighbors_per_group_id[residentGroupId] += disparateNeighbors;

        // add resident's happiness to the group's happiness sum.
        if (_happiness_sum_per_group_id.find(residentGroupId) == _happiness_sum_per_group_id.end())
        {
            _happiness_sum_per_group_id[residentGroupId] = 0;
        }

        _happiness_sum_per_group_id[residentGroupId] += resident->getHappiness();

        // increase the number of residents per this group id
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