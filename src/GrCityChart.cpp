#include "GrCityChart.h"
#include <iostream>

GrCityChart::GrCityChart (
    GrCityChartSizer grCityChartSizer,
    std::unordered_map<const House*, Coordinate> coordToHouseMap,
    std::unordered_map<int, BaseColor> resColors,
    std::unique_ptr<Title> title,
    std::unique_ptr<GrColorKeyPrinter> key,
    std::unique_ptr<Plot> plot,
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int xSpace
): 
    _coord_to_house_map{coordToHouseMap},
    _res_colors{resColors},
    _title{move(title)},
    _key{move(key)},
    _plot{move(plot)},
    _top_left_corner_x__px{topLeftCornerXPx},
    _top_left_corner_y__px{topLeftCornerYPx},
    _x_space__px{xSpace},
    _y_given_space__px{grCityChartSizer.getYSpaceLengthPx()},
    _offset_m{grCityChartSizer.getStartOffsetMultiplier()},
    _overrun_m{grCityChartSizer.getEndOffsetMultiplier()},
    _title_letter{grCityChartSizer.getTitleLetter()},
    _axis_format_X{grCityChartSizer.getAxisFormatX()},
    _axis_format_Y{grCityChartSizer.getAxisFormatX()},
    _cell_size__px{grCityChartSizer.getPixelsPerUnit()},
    _house_min_x{grCityChartSizer.getMinX()},
    _house_max_x{grCityChartSizer.getMaxX()},
    _house_min_y{grCityChartSizer.getMinY()},
    _house_max_y{grCityChartSizer.getMaxY()},
    _x_axis_length__px{  // TODO is calculating axis length here necessary?
        _cell_size__px * (_house_max_x - _house_min_x) + 
        _cell_size__px * _offset_m + 
        _cell_size__px * _overrun_m},
    _cross_hairs_x__px{(_x_space__px - _x_axis_length__px)/2},
    _cross_hairs_y__px{
        _top_left_corner_y__px +
        _title_letter.getHeightIncLSpace() +
        _key->getHeightPx() + 
        _axis_format_X.getAxisHeightPx()
    },
    _pixel_converter_x{std::make_unique<PixelConverter>(
        _house_min_x,
        _cross_hairs_x__px + _cell_size__px * _offset_m,
        _house_max_x,
        _cross_hairs_x__px + _cell_size__px * _offset_m + _cell_size__px * (_house_max_x - _house_min_x))},
    _pixel_converter_y{std::make_unique<PixelConverter>(
        _house_min_y,
        _cross_hairs_y__px +  _cell_size__px * _offset_m,
        _house_max_y,
        _cross_hairs_y__px +  _cell_size__px * _offset_m + _cell_size__px * (_house_max_y - _house_min_y))}
{   
    _title->setTopCenter(topLeftCornerXPx + xSpace/2, topLeftCornerYPx);
    _key->setTopCenter(topLeftCornerXPx + xSpace/2, topLeftCornerYPx + _title->sizeY());
    _plot->moveTopLeft(topLeftCornerXPx, topLeftCornerYPx + _title->sizeY() + _key->getHeightPx());
    _plot->setXYSpacePx(xSpace, _y_given_space__px - _title->sizeY() - _key->sizeY());
    _house_size__px = grCityChartSizer.getDotSize__px();

    _house_min_x__px = _pixel_converter_x->getPixel(_house_min_x);
    _house_max_x__px = _pixel_converter_x->getPixel(_house_max_x);
    _house_min_y__px = _pixel_converter_y->getPixel(_house_min_y);
    _house_max_y__px = _pixel_converter_x->getPixel(_house_max_y);
  
    _title_x__px = _cross_hairs_x__px + (_x_axis_length__px/2);
    _title_y__px = _top_left_corner_y__px;

    //addCityXAxis();
    //addCityYAxis();
}

void GrCityChart::addCityXAxis()
{   
    int length__coord = _house_max_x - _house_min_x;
    _x_axis_utility = std::make_unique<XAxisL2RTop>(
        "", // no axis title
        _pixel_converter_x.get(),
        _axis_format_X,
        _cross_hairs_x__px,
        _cross_hairs_y__px,
        _house_min_x,
        _house_max_x,
        majTickSpacing(length__coord),
        minTickSpacing(length__coord),
        labelSpacing(length__coord),
        _overrun_m * _cell_size__px
    );
}

void GrCityChart::addCityYAxis()
{   
    int length__coord = _house_max_y - _house_min_x;
    _y_axis_utility = std::make_unique<YAxisT2B>(
        "", // no axis title
        _pixel_converter_y.get(),
        _axis_format_Y,
        _cross_hairs_x__px,
        _cross_hairs_y__px,
        _house_min_y,
        _house_max_y,
        majTickSpacing(length__coord),
        minTickSpacing(length__coord),
        labelSpacing(length__coord),
        _overrun_m * _cell_size__px
    );
}

void GrCityChart::print(
    std::unordered_map<const House*, const Resident*> houseToResMap,
    Renderer* renderer
)
{   (void)houseToResMap;
    //printTitle(renderer);
    _title->print(renderer);
    //printXAxis(renderer);
    //printYAxis(renderer);
    //printHouses(houseToResMap, renderer);
    std::cout << "GrCityChart print" << std::endl;
    _plot->print(
        createVectorsOfHousesForEachColor(houseToResMap),
        false,
        renderer
    );
    _key->print(renderer);
}

void GrCityChart::printTitle(Renderer* renderer)
{   
    renderer->setTextFormats({100, 100, 100, 100},
                              {0xAA, 0xFF, 0xFF, 0xFF},
                              _title_letter.letterHeight());
    renderer->renderText(_title_x__px, _title_y__px, _main_title, 1);
}

void GrCityChart::printXAxis(Renderer* renderer)
{   
    _x_axis_utility->print(renderer);
}

void GrCityChart::printYAxis(Renderer* renderer)
{   //TODO y axis isn't printing the 110 number, the largest y value label
// TODO don't let cell size become too large either.
    _y_axis_utility->print(renderer);
}

void GrCityChart::printHouses (
    std::unordered_map<const House *, const Resident *> houseToResMap,
    Renderer* renderer
)
{   (void) renderer;
    std::unordered_map<Color, std::vector<Point>> pointsPerColor =
        createVectorsOfHousesForEachColor(houseToResMap);
    
    //_plot->print(pointsPerColor, false, renderer);
    
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

        //int pixelsX = _pixel_converter_x->getPixel(coord.getX()) - _house_size__px / 2;
        //int pixelsY = _pixel_converter_y->getPixel(coord.getY()) - _house_size__px / 2;
        Point point{(double)coord.getX(), (double)coord.getY(), colorKey};
        colorToCoordinatesMap[colorKey].push_back(point);
        
    }
    return colorToCoordinatesMap;
}

int GrCityChart::majTickSpacing (int axisLength__coord)
 {
    return ( axisLength__coord <= 100)? 1 : 5;
 }
        
int GrCityChart::minTickSpacing (int axisLength__coord)
{
    return (axisLength__coord <= 100)? 1 : 5;
}

int GrCityChart::labelSpacing (int axisLength__coord)
{
    return (axisLength__coord <= 10)? 1 : 10;
}

int GrCityChart::calcHouseSizePx ()
{
    if (_cell_size__px < 4)
        return 0;
    int houseSize = _cell_size__px / 2;
    
    return ( _cell_size__px % 2 == 0) ? houseSize : (houseSize + 1);
}