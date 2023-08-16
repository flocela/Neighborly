#include "GrDvstyChart.h"

using namespace std;

GrDvstyChart::GrDvstyChart (
        std::unordered_map<int, BaseColor> colors,
        std::set<Mood> moods,
        std::unique_ptr<Title> title,
        std::unique_ptr<GrColorKey> colorKey,
        std::unique_ptr<Plot> plot,
        int topLeftXPx,
        int topLeftYPx,
        int xSpace,
        int ySpace
):  _b_color_per_group_id{colors},
    _moods{moods},
    _title{move(title)},
    _key{move(colorKey)},
    _plot{std::move(plot)}
{   
    // x-coordinate of plot's top-left corner aligns with topLeftXPx.
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

void GrDvstyChart::print (
    const unordered_map<int, int>& numOfResidentsPerGroupId,
    const unordered_map<int, int>& numOfDiffNeighborsPerGroupId,
    int run,
    Renderer* renderer
) const
{
    // Plot will print Points. Points have an x-coordinate, y-coordinate, and color.
    // The diversity for a resident is the number of disperate neighbors the resident has.
    // The Point's y value is the average diversity for the residents in the group.
    // The Point's x value is the run number.
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
            (double)numOfDiffNeighborsPerGroupId.at(groupId)/numOfResidentsInGroup;

        Color groupColor = _colorrs_map.at(_b_color_per_group_id.at(groupId)).at(Mood::neutral)._color;
        points.push_back(Point((double)run, averageNumOfDiffNeighbors, groupColor));
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

int GrDvstyChart::sizeXPx () const
{
    return _plot->sizeXPx();
}

int GrDvstyChart::sizeYPx () const
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}