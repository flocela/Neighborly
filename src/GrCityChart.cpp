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
    _plot->setTopLeft(topLeftCornerXPx, topLeftCornerYPx + _title->sizeYPx() + _key->sizeYPx());
    _plot->setXYSpacePx(xSpace, _y_space__px - _title->sizeYPx() - _key->sizeYPx());
    _title->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftCornerYPx);
    _key->setTopCenter(_plot->getCenterValueOfXAxisPx(), topLeftCornerYPx + _title->sizeYPx());
}

void GrCityChart::print(
    const ResPerHouse& houseToResMap,
    Renderer* renderer
) const
{   
    _title->print(renderer);
    _key->print(renderer);
    _plot->print(
        _clearing_vector,
        false,
        renderer
    );
    _plot->print(
        createVectorOfPoints(houseToResMap),
        false,
        renderer
    );
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

        // house color, which is absent if empty, or the resident group color if not empty.
        Color color; 

        // if house is empty then color is Color::absent.
        if (!residentPerHouse.contains(house))
        {
            color = Color::absent;
        }
        else
        {
            const Resident *res = residentPerHouse.at(house);
            int groupId = res->getGroupId();
            double happinessGoal  = res->getHappinessGoal();
            double happinessValue = res->getHappiness();

            Mood mood = Mood::happy;
            if (happinessValue < happinessGoal)
            {
                mood = Mood::unhappy;
            }

            color = _colorrs_map.at(_resident_b_color_per_groupid.at(groupId)).at(mood)._color;
                
        }

        points.emplace_back(Point{(double)coord.getX(), (double)coord.getY(), color});
    }

    return points;
}

vector<Point> GrCityChart::createVectorForClearingGrid ()
{
    // every house needs to have a Color::absent Point.
    vector<Point> points{};

    for (auto const& x : _coordinate_per_house)
    {
        Coordinate coord = x.second;
        points.emplace_back(Point{(double)coord.getX(), (double)coord.getY(), Color::absent});
    }
    return points;
}