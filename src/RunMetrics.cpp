#include "RunMetrics.h"

using namespace std;

RunMetrics::RunMetrics (
    const SetOfHousesPerHouse& adjacentHousesPerHouse
):
    _adj_houses{adjacentHousesPerHouse}
{}

void RunMetrics::updateMetrics(int run, const ResPerHouse residentsPerHouse)
{   
    // Clear previous run's metrics.
    _residents_per_house = move(residentsPerHouse);
    _num_of_residents_per_group_id = unordered_map<int, int>{};
    _num_of_diff_neighbors_per_group_id = unordered_map<int, int>{};
    _happiness_sum_per_group_id = unordered_map<int, double>{};

    // Set run number
    _run_num = run;
    
    // Populate run's metrics.
    for (auto houseAndResident : residentsPerHouse)
    {   
        const House* curHouse = houseAndResident.first;
        const Resident* curRes = houseAndResident.second;
        int curGroupId = curRes->getGroupId();

        // Add number of disparate neighbors to sum of different neighbors for this group's id.

        // Add curGroupId key to _num_of_diff_neighbors_per_group_id map if it does not exist.
        if ( _num_of_diff_neighbors_per_group_id.find(curGroupId) ==
             _num_of_diff_neighbors_per_group_id.end() )
        {
            _num_of_diff_neighbors_per_group_id[curGroupId] = 0;
        }

        // Inspect all houses adjacent to curRes's house to count number of neighbors 
        // with a different groupId than curRes.
        const unordered_set<const House*>& adjacentHouses = _adj_houses.at(curHouse);

        for (const House* adjacentHouse : adjacentHouses)
        {
            // if adjacent house is not empty
            if (residentsPerHouse.contains(adjacentHouse))
            {
                int adj_res_groupId = (residentsPerHouse.at(adjacentHouse))->getGroupId();
                if (adj_res_groupId != curRes->getGroupId())
                {
                    _num_of_diff_neighbors_per_group_id[curGroupId] += 1;
                }
            }
        }

        // Add resident's happiness to the group's happiness sum.
        if (_happiness_sum_per_group_id.find(curGroupId) == _happiness_sum_per_group_id.end())
        {
            _happiness_sum_per_group_id[curGroupId] = 0;
        }
        
        _happiness_sum_per_group_id[curGroupId] += curRes->getHappiness();

        // Increase the number of residents per resident's group id
        if (_num_of_residents_per_group_id.find(curGroupId) ==
            _num_of_residents_per_group_id.end())
        {
            _num_of_residents_per_group_id[curGroupId] = 0;
        }
        _num_of_residents_per_group_id[curGroupId] += 1;
        
    }
}

const ResPerHouse& RunMetrics::getResidentsPerHouse() const
{
    return _residents_per_house;
}

const unordered_map<int, int>& RunMetrics::getNumOfResidentsPerGroupId () const
{
    return _num_of_residents_per_group_id;
}

const unordered_map<int, int>& RunMetrics::getNumOfDiffNeighborsPerGroupId () const
{
    return _num_of_diff_neighbors_per_group_id;
}

const unordered_map<int, double>& RunMetrics::getHappinessSumPerGroupId () const
{
    return _happiness_sum_per_group_id;
}

int RunMetrics::getRunNumber () const
{
    return _run_num;
}