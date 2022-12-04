#include "GrCityChart.h"
#include <iostream>

GrCityChart::GrCityChart (
    std::unordered_map<const House*, Coordinate> coordToHouseMap,
    std::unordered_map<int, BaseColor> resColors,
    std::unique_ptr<Title> title,
    std::unique_ptr<GrColorKeyPrinter> key,
    std::unique_ptr<Plot> plot,
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int xSpace,
    int ySpace
): 
    _coord_to_house_map{coordToHouseMap},
    _res_colors{resColors},
    _title{move(title)},
    _key{move(key)},
    _plot{move(plot)},
    _top_left_corner_x__px{topLeftCornerXPx},
    _top_left_corner_y__px{topLeftCornerYPx},
    _x_space__px{xSpace},
    _y_space__px{ySpace}
{   
    _title->setTopCenter(topLeftCornerXPx + xSpace/2, topLeftCornerYPx);
    _key->setTopCenter(topLeftCornerXPx + xSpace/2, topLeftCornerYPx + _title->sizeYPx());
    _plot->setTopLeft(topLeftCornerXPx, topLeftCornerYPx + _title->sizeYPx() + _key->sizeYPx());
    _plot->setXYSpacePx(xSpace, _y_space__px - _title->sizeYPx() - _key->sizeYPx());
}

void GrCityChart::print(
    std::unordered_map<const House*, const Resident*> houseToResMap,
    Renderer* renderer
)
{   
    _title->print(renderer);
    _plot->print(
        createVectorsOfHousesForEachColor(houseToResMap),
        false,
        renderer
    );
    _key->print(renderer);
}

std::unordered_map<Color, std::vector<Point>> GrCityChart::createVectorsOfHousesForEachColor(
    std::unordered_map<const House *, const Resident *> houseToResMap)
{   
    std::unordered_map<Color, std::vector<Point>> colorToCoordinatesMap = {};

    for (auto const &x : _coord_to_house_map)
    {   
        const House* house = x.first;
        Coordinate coord = x.second;

        Color colorKey;
        if (houseToResMap.find(house) == houseToResMap.end())
        {
            // No resident has this address. So this house is empty.
            colorKey = Color::absent;
        }
        else
        {
            const Resident *res = houseToResMap[house];
            
            double happinessGoal  = res->getHappinessGoal();
            double happinessValue = res->getHappiness();
            if (happinessValue < happinessGoal)
                colorKey = _colorrs_map[_res_colors[res->getGroupNumber()]][Mood::unhappy]._my_color;
            else
                colorKey = _colorrs_map[_res_colors[res->getGroupNumber()]][Mood::happy]._my_color;
        }
        
        if (colorToCoordinatesMap.find(colorKey) == colorToCoordinatesMap.end()) // TODO  c++ knows how to do this in one step
        {
            std::vector<Point> newPointVector = {};
            colorToCoordinatesMap[colorKey] = newPointVector;
        }

        Point point{(double)coord.getX(), (double)coord.getY(), colorKey};
        colorToCoordinatesMap[colorKey].push_back(point);
        
    }
    return colorToCoordinatesMap;
}

int GrCityChart::sizeXPx ()
{
    return _plot->sizeXPx();
}

int GrCityChart::sizeYPx ()
{
    return _title->sizeYPx() + _key->sizeYPx() + _plot->sizeYPx();
}