#include "GrHapChart.h"
using namespace std;

GrHapChart::GrHapChart (
        std::unordered_map<int, BaseColor> colors,
        std::unique_ptr<Title> title,
        std::unique_ptr<ColorKey> colorKey,
        std::unique_ptr<Plot> plot,
        int topLeftXPx,
        int topLeftYPx,
        int xSpace,
        int ySpace
): _colors{colors},
   _title{move(title)},
   _key{move(colorKey)},
   _plot{std::move(plot)}
{   
    _plot->setTopLeft(topLeftXPx, topLeftYPx + _title->sizeYPx() + _key->sizeYPx());
    _plot->setXYSpacePx(xSpace, ySpace - _title->sizeYPx() - _key->sizeYPx());
    _title->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftYPx);
    _key->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftYPx + _title->sizeYPx());
}

void GrHapChart::print (
    unordered_map<const Resident*, const House*> housePerResident,
    int run,
    Renderer* renderer
) const
{
    // add the residents' happiness per each group
    // assume the happiness has been calculated.
    unordered_map<int, double> happinessSumPerGroup;

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