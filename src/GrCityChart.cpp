#include "GrCityChart.h"
#include <iostream>

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
    _plot->setTopLeft(topLeftCornerXPx, topLeftCornerYPx + _title->sizeYPx() + _key->sizeYPx());
    _plot->setXYSpacePx(xSpace, _y_space__px - _title->sizeYPx() - _key->sizeYPx());
    _title->setTopCenter(_plot->centerValueOfXAxisPx(), topLeftCornerYPx);
    _key->setTopCenter(_plot->centerValueOfXAxisPx(), topLeftCornerYPx + _title->sizeYPx());
}

void GrCityChart::print(
    unordered_map<const House*, const Resident*> houseToResMap,
    Renderer* renderer
)
{   
    _title->print(renderer);
    _key->print(renderer);
    _plot->print(
        createVectorPerColorForClearingPlot(),
        false,
        renderer
    );
    _plot->print(
        createVectorsOfPointsPerColor(houseToResMap),
        false,
        renderer
    );
}


int GrCityChart::sizeXPx ()
{
    return _plot->sizeXPx();
}

int GrCityChart::sizeYPx ()
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}

unordered_map<Color, vector<Point>> GrCityChart::createVectorsOfPointsPerColor (
    unordered_map<const House *, const Resident *> residentPerHouse
)
{   
    unordered_map<Color, vector<Point>> pointsPerColor = {};

    for (auto const &x : _coordinate_per_house)
    {   
        const House* house = x.first;
        Coordinate coord = x.second;

        // house color, which is absent if empty, or the resident group color if not empty.
        Color color; 

        // if house is empty then color is Color::absent.
        if (residentPerHouse.find(house) == residentPerHouse.end()) 
        {
            color = Color::absent;
        }
        else
        {
            const Resident *res = residentPerHouse[house];
            
            double happinessGoal  = res->getHappinessGoal();
            double happinessValue = res->getHappiness();
            if (happinessValue < happinessGoal)
                color = _colorrs_map[_resident_b_color_per_groupid[res->getGroupNumber()]]
                        [Mood::unhappy]._color;
            else
                color = _colorrs_map[_resident_b_color_per_groupid[res->getGroupNumber()]]
                        [Mood::happy]._color;
        }

        Point point{(double)coord.getX(), (double)coord.getY(), color};
        
        if (pointsPerColor.find(color) == pointsPerColor.end())
        {
            pointsPerColor[color] = {};
        }

        pointsPerColor[color].push_back(point);
    }

    return pointsPerColor;
}

unordered_map<Color, vector<Point>> GrCityChart::createVectorPerColorForClearingPlot ()
{
    // every house needs to have a Color::absent Point.
    unordered_map<Color, vector<Point>> pointsPerColor = {};

    for (auto const& x : _coordinate_per_house)
    {
        Coordinate coord = x.second;

        pointsPerColor[Color::absent].push_back({(double)coord.getX(),
                                                 (double)coord.getY(),
                                                 Color::absent});
    }
    return pointsPerColor;
}