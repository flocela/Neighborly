#include "GrCityPrinter.h"
#include <iostream>

GrCityPrinter::GrCityPrinter (
    GrCityPrinterSizer grCityPrinterSizer,
    Renderer* renderer,
    std::map<Coordinate, House*> coordToHouseMap,
    std::unordered_map<int, Color> resColors,
    int topLeftCornerXPx,
    int topLeftCornerYPx
) : _renderer{renderer},
    _coord_to_house_map{coordToHouseMap},
    _res_colors{resColors},
    _top_left_corner_x__px{topLeftCornerXPx},
    _top_left_corner_y__px{topLeftCornerYPx},
    _x_given_space__px{grCityPrinterSizer.getXSpaceLengthPx()},
    _y_given_space__px{grCityPrinterSizer.getYSpaceLengthPx()},
    _offset__px{grCityPrinterSizer.getStartOffset()},
    _overrun__px{grCityPrinterSizer.getEndOffset()},
    _title_letter{grCityPrinterSizer.getTitleLetter()},
    _axis_format_X{grCityPrinterSizer.getAxisFormatX()},
    _axis_format_Y{grCityPrinterSizer.getAxisFormatX()},
    _cell_size__px{grCityPrinterSizer.getPixelsPerUnitX()},
    _house_min_x{grCityPrinterSizer.getMinX()},
    _house_max_x{grCityPrinterSizer.getMaxX()},
    _house_min_y{grCityPrinterSizer.getMinY()},
    _house_max_y{grCityPrinterSizer.getMaxY()},
    _x_axis_length__px{
        _cell_size__px * (_house_max_x - _house_min_x) + 
        _offset__px + 
        _overrun__px},
    _cross_hairs_x__px{(_x_given_space__px - _x_axis_length__px)/2},
    _key{
        _cross_hairs_x__px,
        _top_left_corner_y__px + _title_letter.getHeightIncLSpace(),
        _x_axis_length__px,
        grCityPrinterSizer.getKeyLetter(),
        _res_colors,
        {"happy", "unhappy"}
    },
    _cross_hairs_y__px{
        _top_left_corner_y__px +
        _title_letter.getHeightIncLSpace() +
        _key.getHeightPx() + 
        _axis_format_X.getAxisHeightPx()
    },
    
    
    _pixel_converter_x{ std::make_unique<PixelConverter>(
        _house_min_x,
        _cross_hairs_x__px + _offset__px,
        _house_max_x,
        _cross_hairs_x__px + _offset__px + _cell_size__px * (_house_max_x - _house_min_x))
    },
    _pixel_converter_y{ std::make_unique<PixelConverter>(
        _house_min_y,
        _cross_hairs_y__px + _offset__px,
        _house_max_y,
        _cross_hairs_y__px + _offset__px + _cell_size__px * (_house_max_y - _house_min_y))
    }
{  
    _axis_format_X.setTitleLetterHeight(0);// axis title is empty string.
    _axis_format_Y.setTitleLetterHeight(0);// axis title is empty string.
    
    _house_size__px = calcHouseSizePx();

    _house_min_x__px = _pixel_converter_x->getPixel(_house_min_x);
    _house_max_x__px = _pixel_converter_x->getPixel(_house_max_x);
    _house_min_y__px = _pixel_converter_y->getPixel(_house_min_y);
    _house_max_y__px = _pixel_converter_x->getPixel(_house_max_y);
  
    _title_x__px = _cross_hairs_x__px + (_x_axis_length__px/2);
    _title_y__px = _top_left_corner_y__px;

    addCityXAxis();
    addCityYAxis();
}

void GrCityPrinter::addCityXAxis()
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
        labelSpacing(length__coord)
    );
}

void GrCityPrinter::addCityYAxis()
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
        labelSpacing(length__coord)
    );
}

void GrCityPrinter::printCity(std::unordered_map<House*, Resident*> houseToResMap)
{   
    printTitle();
    printXAxis();
    printYAxis();
    printHouses(houseToResMap);
    _key.print(_renderer);
}

void GrCityPrinter::printTitle()
{   
    _renderer->setTextFormats({100, 100, 100, 100},
                              {0xAA, 0xFF, 0xFF, 0xFF},
                              _title_letter.letterHeight());
    _renderer->renderText(_title_x__px, _title_y__px, _main_title, 1);
}

void GrCityPrinter::printXAxis()
{   
    _x_axis_utility->print(_renderer);
}

void GrCityPrinter::printYAxis()
{   //TODO y axis isn't printing the 110 number, the largest y value label
// TODO don't let cell size become too large either.
    _y_axis_utility->print(_renderer);
}

void GrCityPrinter::printHouses( std::unordered_map<House *, Resident *> houseToResMap )
{   
    std::map<Color, std::vector<Coordinate>> coordsPerColor =
        createVectorsOfHousesForEachColor(houseToResMap);
    
    
    for (auto const &colorToCoordVector : coordsPerColor)
    {
        _renderer->addBlocksByColor(
            _house_size__px,
            _house_size__px,
            colorToCoordVector.second,
            _the_color_infos[colorToCoordVector.first].rgba);
    }
}

std::map<Color, std::vector<Coordinate>> GrCityPrinter::createVectorsOfHousesForEachColor(
    std::unordered_map<House *, Resident *> houseToResMap)
{   
    std::map<Color, std::vector<Coordinate>> colorToCoordinatesMap = {};

    for (auto const &x : _coord_to_house_map)
    {   
        Coordinate coord = x.first;
        House *house = x.second;
        Color colorKey;
        if (houseToResMap.find(house) == houseToResMap.end())
        {
            // No resident has this address. So this house is empty.
            colorKey = Color::absent;
        }
        else
        {
            Resident *res = houseToResMap[house];
            
            double happinessGoal  = res->getHappinessGoal();
            double happinessValue = res->getHappiness();
            if (happinessValue < happinessGoal)
                colorKey = _color_map[_res_colors[res->getGroupNumber()]]["unhappy"];
            else
                colorKey = _color_map[_res_colors[res->getGroupNumber()]]["happy"];
        }
        
        if (colorToCoordinatesMap.find(colorKey) == colorToCoordinatesMap.end()) // TODO  c++ knows how to do this in one step
        {
            std::vector<Coordinate> newCoordinateVector = {};
            colorToCoordinatesMap[colorKey] = newCoordinateVector;
        }
        
        int pixelsX = _pixel_converter_x->getPixel(coord.getX()) - _house_size__px / 2;
        int pixelsY = _pixel_converter_y->getPixel(coord.getY()) - _house_size__px / 2;
        Coordinate pixelCoord{pixelsX, pixelsY};
        colorToCoordinatesMap[colorKey].push_back(pixelCoord);
        
    }
    return colorToCoordinatesMap;
}

Color GrCityPrinter::getHappyColor (int resGroup)
{
    return _color_map[_res_colors[resGroup]]["happy"];
}

Color GrCityPrinter::getUnhappyColor (int resGroup)
{
    return _color_map[_res_colors[resGroup]]["unhappy"];
}

int GrCityPrinter::majTickSpacing (int axisLength__coord)
 {
    return ( axisLength__coord <= 100)? 1 : 5;
 }
        
int GrCityPrinter::minTickSpacing (int axisLength__coord)
{
    return (axisLength__coord <= 100)? 1 : 5;
}

int GrCityPrinter::labelSpacing (int axisLength__coord)
{
    return (axisLength__coord <= 10)? 1 : 10;
}

int GrCityPrinter::calcYCrossHairsPx ()
{
    std::cout << "GrCityPrinter _key.getHeightPx(): " << _key.getHeightPx() << std::endl;
    return _top_left_corner_y__px + 
           _title_letter.getHeightIncLSpace() + 
           _key.getHeightPx() +
           _axis_format_X.getAxisHeightPx();
}

int GrCityPrinter::calcCellSizePx ()
{
    // X-direction
    int xAxisLengthPx = _x_given_space__px - _axis_format_Y.getAxisHeightPx(); 
    int numOfCellsX = (_house_max_x - _house_min_x) + _offset__px + _overrun__px;
    int xCellSize = xAxisLengthPx / numOfCellsX;

    // Y-direction
    int yAxisLengthPx = 
        _y_given_space__px - 
        _title_letter.getHeightIncLSpace() -
        _axis_format_X.getAxisHeightPx();
    int numOfCellsY = (_house_max_y - _house_min_y) + _offset__px + _overrun__px;
    int yCellSize = yAxisLengthPx / numOfCellsY;
    int smallestCellSize = std::min(xCellSize, yCellSize);
    smallestCellSize = (smallestCellSize%2 == 0)? smallestCellSize : (smallestCellSize+1);
    // TODO if yCellSize or xCellSize is less than four, then throw an exception.
    return (smallestCellSize < 4)? 4: smallestCellSize;
}

int GrCityPrinter::calcHouseSizePx ()
{
    if (_cell_size__px < 4)
        return 0;
    int houseSize = _cell_size__px / 2;
    
    return ( houseSize % 2 == 0) ? houseSize : (houseSize + 1);
}

