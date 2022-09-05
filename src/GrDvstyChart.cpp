#include "GrDvstyChart.h"

void GrDvstyChart::print (
    std::unordered_map<const Resident*, const House*> housePerResident,
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run,
    Renderer* renderer
)
{
    /*(void)city;
    (void)housePerResident;
    (void)residentPerHouse;
    (void)renderer;*/

    // count the number of different neighbors for each group.
    std::unordered_map<int, int> count_diff_neighbors_Per_group;

    // number of residents per group
    std::unordered_map<int, int> count_residents_Per_group;

    for (std::pair<const Resident*, const House*> ii : housePerResident)
    {
        const Resident* res = ii.first;
        const House* house = ii.second;
        int groupNumForRes = res->getGroupNumber();
        std::set<const House*> adjHouses = _neighbors[house];
        std::set<const Resident*> adjResidents = getResidentsInTheseHouses(adjHouses, residentPerHouse);

        for (const Resident* adj : adjResidents)
        {
            int groupNumForAdj = adj->getGroupNumber();
            if (groupNumForAdj == groupNumForRes)
            {
                continue;
            }
            if (count_diff_neighbors_Per_group.find(groupNumForAdj) == count_diff_neighbors_Per_group.end())
            {
                count_diff_neighbors_Per_group[groupNumForAdj] = 1;
            }
            else
            {
                count_diff_neighbors_Per_group[groupNumForAdj] = count_diff_neighbors_Per_group[groupNumForAdj] + 1;
            }
        }

        if (count_residents_Per_group.find(groupNumForRes) == count_residents_Per_group.end())
        {
            count_residents_Per_group[groupNumForRes] = 1;
        }
        else
        {
            count_residents_Per_group[groupNumForRes] = count_residents_Per_group[groupNumForRes] + 1;
        }
        
    }

    std::vector<Point> points;
    for (auto jj : count_residents_Per_group)
    {
        int groupNum = jj.first;
        int countInGroup = jj.second;
        double averageNumDiff = (double)count_diff_neighbors_Per_group[groupNum]/countInGroup;
        // TODO emplace
        points.push_back(Point{(double)run, averageNumDiff, _colors[groupNum], "neutral"});
    }
    _chart.print(points, false, renderer);
    _key.print(renderer);
}

std::set<const Resident*> GrDvstyChart::getResidentsInTheseHouses (
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