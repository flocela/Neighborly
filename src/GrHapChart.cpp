#include "GrHapChart.h"
using namespace std;

GrHapChart::GrHapChart (
        std::unordered_map<int, BaseColor> colors,
        std::unique_ptr<Title> title,
        std::unique_ptr<GrColorKey> colorKey,
        std::unique_ptr<Plot> plot,
        int topLeftXPx,
        int topLeftYPx,
        int xSpace,
        int ySpace
): _base_color_per_group_id{colors},
   _title{move(title)},
   _key{move(colorKey)},
   _plot{std::move(plot)}
{   
    // x-coordinate of plot's top left corner aligns with topLeftXPx.
    // Plot is below the title and below the key.
    // The available space in the x direction is xSpace.
    // The available space in the y direction is decreased by the title and the key.
    _plot->setPlot(
        topLeftXPx,
        topLeftYPx + _title->sizeYPx() + _key->sizeYPx(),
        xSpace,
        ySpace - _title->sizeYPx() - _key->sizeYPx()
    );

    // In the x-direction, center title and key with the center of the plot.
    // Title is at the top of the chart.
    _title->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftYPx);

    // Key is below the title.
    _key->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftYPx + _title->sizeYPx());
}

void GrHapChart::print (
    const unordered_map<int, int>& numofResidentsPerGroup,
    const unordered_map<int, double>& happinessSumPerGroup,
    int run,
    Renderer* renderer
) const
{
    // plot will print points.
    // The point's y value is the average happiness for the group.
    // The point's x value is the run number.
    vector<Point> points{};
    for (auto resCountPerGroup : numofResidentsPerGroup)
    {
        int groupId = resCountPerGroup.first;
        int countInGroup = resCountPerGroup.second;
        if (countInGroup == 0)
        {
            continue;
        }
        double aveHappiness = happinessSumPerGroup.at(groupId)/countInGroup;
        Color c = _colorrs_map.at(_base_color_per_group_id.at(groupId)).at(Mood::neutral)._color;
        points.push_back( Point( (double)run, aveHappiness, c));
    }

    // Only print the key once.
    if (!_key_has_printed)
    {
        _key->print(renderer);
        _key_has_printed = true;
    }

    // Only print the title once.
    if (!_title_has_printed)
    {
        _title->print(renderer);
        _title_has_printed = true;
    }
    
    _plot->print(points, false, renderer);
}

int GrHapChart::sizeXPx () const
{
    return _plot->sizeXPx();
}

int GrHapChart::sizeYPx () const
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}