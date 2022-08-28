#include "GrHapPrinter.h"

void GrHapPrinter::print (
    City* city, 
    std::unordered_map<Resident*, House*> housePerResident,
    std::unordered_map<House*, Resident*> residentPerHouse,
    int run,
    Renderer* renderer
)
{
    (void)city;
    (void)residentPerHouse;
    /*(void)housePerResident;
    (void)renderer;*/

    // sum the happiness per each group
    // assume the happiness has been calculated.
    std::unordered_map<int, int> happiness_sum_Per_group;

    // number of residents per group
    std::unordered_map<int, int> count_residents_Per_group;

    for (auto& pair : housePerResident)
    {
        Resident* res = pair.first;
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
        double averageNumDiff = (double)happiness_sum_Per_group[groupNum]/countInGroup;
        // TODO emplace
        points.push_back(Point{(double)run, averageNumDiff, _colors[groupNum], "neutral"});
    }
    _chart.print(points, false, renderer);
    _key.print(renderer);
}

std::set<Resident*> GrHapPrinter::getResidentsInTheseHouses (
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