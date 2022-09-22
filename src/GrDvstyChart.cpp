#include "GrDvstyChart.h"

void GrDvstyChart::print (
    std::unordered_map<const Resident*, const House*> housePerResident,
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run,
    Renderer* renderer
)
{
    std::unordered_map<int, int> num_of_diff_neighbors_Per_group;

    std::unordered_map<int, int> num_of_residents_Per_group;

    for (std::pair<const Resident*, const House*> ii : housePerResident)
    {
        const Resident* res = ii.first;
        const House* house = ii.second;

        int groupId = res->getGroupNumber();
        std::set<const House*> adjHouses = _adj_neighbors[house];
        std::set<const Resident*> adjResidents = getResidentsInHouses(adjHouses, residentPerHouse);

        for (const Resident* adj : adjResidents)
        {
            int neighborGroupId = adj->getGroupNumber();
            if (neighborGroupId == groupId)
            {
                continue;
            }
            if (num_of_diff_neighbors_Per_group.find(neighborGroupId) == num_of_diff_neighbors_Per_group.end())
            {
                num_of_diff_neighbors_Per_group[neighborGroupId] = 1;
            }
            else
            {
                num_of_diff_neighbors_Per_group[neighborGroupId] += 1;
            }
        }

        if (num_of_residents_Per_group.find(groupId) == num_of_residents_Per_group.end())
        {
            num_of_residents_Per_group[groupId] = 1;
        }
        else
        {
            num_of_residents_Per_group[groupId] += 1;
        }
        
    }

    std::vector<Point> points;
    for (auto jj : num_of_residents_Per_group)
    {
        int groupId = jj.first;
        int countInGroup = jj.second;
        double averageNumOfDiffNeighbors = 
            (double)num_of_diff_neighbors_Per_group[groupId]/countInGroup;
        points.emplace_back( Point{
            (double)run, 
            averageNumOfDiffNeighbors,
            _colorrs_map[_colors[groupId]][Mood::neutral]._my_color} );
    }
    
    _title->print(renderer);
    _plot->print(points, false, renderer);
    _key->print(renderer);
}

std::set<const Resident*> GrDvstyChart::getResidentsInHouses (
    std::set<const House*> houses,
    const std::unordered_map<const House*, const Resident*> residentPerHouse
)
{
    std::set<const Resident*> residents;
    for (const House* house : houses)
    {
        if (residentPerHouse.find(house) != residentPerHouse.end())
        {
            residents.insert(residentPerHouse.at(house));
        }
    }

    return residents;
}