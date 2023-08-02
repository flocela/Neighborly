#include "GrCityChart.h"
#include <iostream>
#include "Point.h"

using namespace std;

GrCityChart::GrCityChart (
    unordered_map<const House*, Coordinate> coordPerHouseMap,
    unordered_map<int, BaseColor> resColors,
    unique_ptr<Title> title,
    unique_ptr<GrColorKey> key,
    unique_ptr<Plot> plot,
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int xSpace,
    int ySpace
): 
    _coordinate_per_house{coordPerHouseMap},
    _resident_b_color_per_groupid{resColors},
    _title{move(title)},
    _key{move(key)},
    _plot{move(plot)},
    _top_left_corner_x__px{topLeftCornerXPx},
    _top_left_corner_y__px{topLeftCornerYPx},
    _x_space__px{xSpace},
    _y_space__px{ySpace}
{   
    _clearing_vector = createVectorForClearingGrid();
    
    // Plot's top left corner's x aligns with topLeftCornerXPx.
    // Plot is below the title and the key.
    // Plot's allowable x-space is all the space given by xSpace.
    // Plot's allowable y-space is decreased by the title and key.
    _plot->setPlot(
        topLeftCornerXPx,
        topLeftCornerYPx + _title->sizeYPx() + _key->sizeYPx(),
        xSpace,
        _y_space__px - _title->sizeYPx() - _key->sizeYPx());

    _title->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftCornerYPx);

    // Key is below the title.
    _key->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftCornerYPx + _title->sizeYPx());
}

void GrCityChart::print(const ResPerHouse& houseToResMap, Renderer* renderer) const
{   
    _title->print(renderer);
    _key->print(renderer);

    // Print an empty plot to remove drawing of previous residents and houses.
    _plot->print(_clearing_vector, false, renderer);

    // Print new data on the plot.
    _plot->print(createVectorOfPoints(houseToResMap), false, renderer);
}

int GrCityChart::sizeXPx () const
{
    return _plot->sizeXPx();
}

int GrCityChart::sizeYPx () const
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}

vector<Point> GrCityChart::createVectorOfPoints (const ResPerHouse& residentPerHouse) const
{   
    vector<Point> points{};

    for (auto const &x : _coordinate_per_house)
    {   
        const House* house = x.first;
        Coordinate coord = x.second;

        // Point color
        Color color; 

        // If house is empty then color absent color.
        if (!residentPerHouse.contains(house))
        {
            color = _absent_color;
        }
        else
        {
            // Color depends on group id and mood of the resident.
            // If the resident's happiness value is greater or equal to its happiness goal,
            // then the mood is happy, otherwise it's unhappy.
            const Resident *res = residentPerHouse.at(house);
            int groupId = res->getGroupId();

            Mood mood = Mood::happy;
            if (res->getHappiness() <= res->getHappinessGoal())
            {
                mood = Mood::unhappy;
            }

            color = _colorrs_map.at(_resident_b_color_per_groupid.at(groupId)).at(mood)._color;
                
        }

        // Point is made up of house's coordinate x and y and resident's color.
        points.emplace_back(Point{(double)coord.getX(), (double)coord.getY(), color});
    }

    return points;
}

vector<Point> GrCityChart::createVectorForClearingGrid ()
{
    // Every house needs to have a Color::absent Point.
    vector<Point> points{};

    for (auto const& x : _coordinate_per_house)
    {
        Coordinate coord = x.second;
        points.emplace_back(Point{(double)coord.getX(), (double)coord.getY(), _absent_color});
    }
    return points;
}