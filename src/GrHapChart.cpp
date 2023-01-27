#include "GrHapChart.h"
using namespace std;

void GrHapChart::print (
    unordered_map<const Resident*, const House*> housePerResident,
    int run,
    Renderer* renderer
) const
{
    // add the residents' happiness per each group
    // assume the happiness has been calculated.
    unordered_map<int, int> happinessSumPerGroup;

    // number of residents per group
    unordered_map<int, int> numofResidentsPerGroup;

    for (auto& pair : housePerResident)
    {
        const Resident* res = pair.first;
        int resGroupNumber = res->getGroupId();

        if (happinessSumPerGroup.find(resGroupNumber) != happinessSumPerGroup.end())
        {
            happinessSumPerGroup[resGroupNumber] += res->getHappiness();
        }
        else
        {
            happinessSumPerGroup[resGroupNumber] = res->getHappiness();
        }

        if (numofResidentsPerGroup.find(resGroupNumber) == numofResidentsPerGroup.end())
        {
            numofResidentsPerGroup[resGroupNumber] = 1;
        }
        else
        {
            numofResidentsPerGroup[resGroupNumber] =
                numofResidentsPerGroup[resGroupNumber] + 1;
        }
    }

    vector<Point> points{};
    for (auto resCountPerGroup : numofResidentsPerGroup)
    {
        int groupId = resCountPerGroup.first;
        int countInGroup = resCountPerGroup.second;
        if (countInGroup == 0)
        {
            continue;
        }
        double aveHappiness = (double)happinessSumPerGroup[groupId]/countInGroup;
        Color c = _colorrs_map.at(_colors.at(groupId)).at(Mood::neutral)._color;
        points.push_back( Point( (double)run, aveHappiness, c));
    }

    _title->print(renderer);
    _key->print(renderer);
    _plot->print(points, false, renderer);
}

int GrHapChart::sizeXPx ()
{
    return _plot->sizeXPx();
}

int GrHapChart::sizeYPx ()
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}