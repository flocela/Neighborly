#include "GrDvstyChart.h"

using namespace std;

GrDvstyChart::GrDvstyChart (
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        const SetOfHousesPerHouse& adjacentNeighbors,
        std::unique_ptr<Title> title,
        std::unique_ptr<ColorKey> colorKey,
        std::unique_ptr<Plot> plot,
        int topLeftXPx,
        int topLeftYPx,
        int xSpace,
        int ySpace
):  _b_color_per_groupId{colors},
    _moods{moods},
    _adj_neighbors{adjacentNeighbors},
    _title{move(title)},
    _key{move(colorKey)},
    _plot{std::move(plot)}
{   
    _plot->setTopLeft(topLeftXPx, topLeftYPx + _title->sizeYPx() + _key->sizeYPx());
    _plot->setXYSpacePx(xSpace, ySpace - _title->sizeYPx() - _key->sizeYPx());
    _title->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftYPx);
    _key->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftYPx + _title->sizeYPx());
}

void GrDvstyChart::print (
    unordered_map<int, int> numOfResidentsPerGroupId,
        unordered_map<int, int> numOfDiffNeighborsPerGroupId,
    int run,
    Renderer* renderer
) const
{
    // the diversity for a resident is the number of disperate neighbors the resident has.
    // the Point's y value is the average diversity for the residents in the group.
    // the Point's x value is the run number.
    vector<Point> points{};
    for (auto pair : numOfResidentsPerGroupId)
    {
        int groupId = pair.first;
        int numOfResidentsInGroup = pair.second;
        
        if (numOfResidentsInGroup == 0)
        {
            continue;
        }

        double averageNumOfDiffNeighbors = 
            (double)numOfDiffNeighborsPerGroupId[groupId]/numOfResidentsInGroup;

        Color groupColor = _colorrs_map.at(_b_color_per_groupId.at(groupId)).at(Mood::neutral)._color;
        points.push_back(Point((double)run, averageNumOfDiffNeighbors, groupColor));
    }
    
    if (!_key_has_printed)
    {
        _key->print(renderer);
        _key_has_printed = true;
    }
    if (!_title_has_printed)
    {
        _title->print(renderer);
        _title_has_printed = true;
    }
    
    _plot->print(points, false, renderer);
}

int GrDvstyChart::sizeXPx () const
{
    return _plot->sizeXPx();
}

int GrDvstyChart::sizeYPx () const
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}