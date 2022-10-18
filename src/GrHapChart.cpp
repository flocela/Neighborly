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
    std::unordered_map<int, int> total_residents_Per_group;

    // For each resident, add its resident's happiness to the happiness_sum_Per_group.
    for (auto& pair : housePerResident)
    {
        const Resident* res = pair.first;
        int resGroupNumber = res->getGroupNumber();

        if (happiness_sum_Per_group.find(resGroupNumber) != happiness_sum_Per_group.end())
        {
            happiness_sum_Per_group[resGroupNumber] += res->getHappiness();
        }
        else
        {
            happiness_sum_Per_group[resGroupNumber] = res->getHappiness();
        }

        if (total_residents_Per_group.find(resGroupNumber) == total_residents_Per_group.end())
        {
            total_residents_Per_group[resGroupNumber] = 1;
        }
        else
        {
            total_residents_Per_group[resGroupNumber] =
                total_residents_Per_group[resGroupNumber] + 1;
        }
    }

   std::unordered_map<Color, std::vector<Point>> pointsPerColor;
    for (auto jj : total_residents_Per_group)
    {
        int groupNum = jj.first;
        int countInGroup = jj.second;
        double aveHappiness = (double)happiness_sum_Per_group[groupNum]/countInGroup;
        Color c = _colorrs_map[_colors[groupNum]][Mood::neutral]._my_color;
        pointsPerColor.insert({
            c,
            std::vector<Point>( 1, Point( (double)run, aveHappiness, c) )
        });
    }
    _title->print(renderer);
    _key->print(renderer);
    _plot->print(pointsPerColor, false, renderer);
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

int GrHapChart::sizeXPx ()
{
    return _plot->sizeXPx();
}

int GrHapChart::sizeYPx ()
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}