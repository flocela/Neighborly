#include "GrHapChart.h"

void GrHapChart::print (
    std::unordered_map<const Resident*, const House*> housePerResident,
    int run,
    Renderer* renderer
)
{
    /*(void)housePerResident;
    (void)renderer;*/

    // sum the happiness per each group
    // assume the happiness has been calculated.
    std::unordered_map<int, int> happiness_sum_Per_group;

    // number of residents per group
    std::unordered_map<int, int> count_residents_Per_group;

    for (auto& pair : housePerResident)
    {
        const Resident* res = pair.first;
        int resGroupNumber = res->getGroupNumber();
        if (happiness_sum_Per_group.find(resGroupNumber) != happiness_sum_Per_group.end())
        {
            happiness_sum_Per_group[resGroupNumber] = 
                happiness_sum_Per_group[resGroupNumber] + res->getHappiness();
        }
        else
        {
            happiness_sum_Per_group[resGroupNumber] = res->getHappiness();
        }

        if (count_residents_Per_group.find(resGroupNumber) == count_residents_Per_group.end())
        {
            count_residents_Per_group[resGroupNumber] = 1;
        }
        else
        {
            count_residents_Per_group[resGroupNumber] =
                count_residents_Per_group[resGroupNumber] + 1;
        }
    }

   std::vector<Point> points;
    for (auto jj : count_residents_Per_group)
    {
        int groupNum = jj.first;
        int countInGroup = jj.second;
        double aveHappiness = (double)happiness_sum_Per_group[groupNum]/countInGroup;
        // TODO points doesn't need Mood.
        // TODO emplace
        points.push_back(Point{(double)run, aveHappiness, _colorrs_map[_colors[groupNum]][Mood::neutral]._my_color});
    }
    _plot.print(points, false, renderer);
    _key.print(renderer);
}

std::set<Resident*> GrHapChart::getResidentsInTheseHouses (
    std::set<House*> houses,
    const std::unordered_map<House*, Resident*> residentPerHouse
)
{
    std::set<Resident*> residents;
    for (House* house : houses)
    {
        if (residentPerHouse.find(house) != residentPerHouse.end())
        {
            residents.insert(residentPerHouse.at(house));
        }
    }

    return residents;
}