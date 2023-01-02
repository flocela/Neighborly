#include "GrCityChart.h"
#include <iostream>

using namespace std;

GrCityChart::GrCityChart (
    unordered_map<const House*, Coordinate> coordToHouseMap,
    unordered_map<int, BaseColor> resColors,
    unique_ptr<Title> title,
    unique_ptr<GrColorKeyPrinter> key,
    unique_ptr<Plot> plot,
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int xSpace,
    int ySpace
): 
    _house_per_coordinate{coordToHouseMap},
    _res_colors{resColors},
    _title{move(title)},
    _key{move(key)},
    _plot{move(plot)},
    _top_left_corner_x__px{topLeftCornerXPx},
    _top_left_corner_y__px{topLeftCornerYPx},
    _x_space__px{xSpace},
    _y_space__px{ySpace}
{   
    
    _key->setTopCenter(topLeftCornerXPx + xSpace/2, topLeftCornerYPx + _title->sizeYPx());
    _plot->setTopLeft(topLeftCornerXPx, topLeftCornerYPx + _title->sizeYPx() + _key->sizeYPx());
    _plot->setXYSpacePx(xSpace, _y_space__px - _title->sizeYPx() - _key->sizeYPx());
    _title->setTopCenter(_plot->centerValueOfXAxisPx(), topLeftCornerYPx);
}

void GrCityChart::print(
    unordered_map<const House*, const Resident*> houseToResMap,
    Renderer* renderer
)
{   
    _title->print(renderer);
    _key->print(renderer);
    _plot->print(
        createVectorsForClearingPlot(),
        false,
        renderer
    );
    _plot->print(
        createVectorsOfHousesForEachColor(houseToResMap),
        false,
        renderer
    );
    
}

unordered_map<Color, vector<Point>> GrCityChart::createVectorsForClearingPlot ()
{
    // every house needs to have a Color::absent point.
    unordered_map<Color, vector<Point>> pointsPerColor = {};

    for (auto const& x : _house_per_coordinate)
    {
        Coordinate coord = x.second;

        Point point{(double)coord.getX(), (double)coord.getY(), Color::absent};
        pointsPerColor[Color::absent].push_back(point);
    }
    return pointsPerColor;
}

unordered_map<Color, vector<Point>> GrCityChart::createVectorsOfHousesForEachColor(
    unordered_map<const House *, const Resident *> residentPerHouse)
{   
    unordered_map<Color, vector<Point>> pointsPerColor = {};

    for (auto const &x : _house_per_coordinate)
    {   
        const House* house = x.first;
        Coordinate coord = x.second;

        Color colorKey;
        if (residentPerHouse.find(house) == residentPerHouse.end())
        {
            // No resident has this address. So this house is empty.
            colorKey = Color::absent;
        }
        else
        {
            const Resident *res = residentPerHouse[house];
            
            double happinessGoal  = res->getHappinessGoal();
            double happinessValue = res->getHappiness();
            if (happinessValue < happinessGoal)
                colorKey = _colorrs_map[_res_colors[res->getGroupNumber()]][Mood::unhappy]._color;
            else
                colorKey = _colorrs_map[_res_colors[res->getGroupNumber()]][Mood::happy]._color;
        }

        Point point{(double)coord.getX(), (double)coord.getY(), colorKey};
        
        if (pointsPerColor.find(colorKey) == pointsPerColor.end())
        {
            vector<Point> newPointVector = {};
            pointsPerColor[colorKey] = newPointVector;
        }

        pointsPerColor[colorKey].push_back(point);
        
    }
    return pointsPerColor;
}

int GrCityChart::sizeXPx ()
{
    return _plot->sizeXPx();
}

int GrCityChart::sizeYPx ()
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}