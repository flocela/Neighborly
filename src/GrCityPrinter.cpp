#include "GrCityPrinter.h"
#include <iostream>

GrCityPrinter::GrCityPrinter (
    GrCityPrinterSizer grCityPrinterSizer,
    Renderer* renderer,
    std::map<Coordinate, House*> coordToHouseMap,
    std::map<int, std::pair<Color, Color>> resColors,
    int topLeftCornerXPx,
    int topLeftCornerYPx
) : _renderer{renderer},
    _coord_to_house_map{coordToHouseMap},
    _res_colors{resColors},
    _top_left_corner_x__px{topLeftCornerXPx},
    _top_left_corner_y__px{topLeftCornerYPx},
    _x_given_space__px{grCityPrinterSizer.getXSpaceLengthPx()},
    _y_given_space__px{grCityPrinterSizer.getYSpaceLengthPx()},
    _axis_format_X{grCityPrinterSizer.getAxisFormatX()},
    _axis_format_Y{grCityPrinterSizer.getAxisFormatX()},
    _title_letter{grCityPrinterSizer.getTitleLetter()},
    _house_min_x{grCityPrinterSizer.getMinX()},
    _house_max_x{grCityPrinterSizer.getMaxX()},
    _house_min_y{grCityPrinterSizer.getMinY()},
    _house_max_y{grCityPrinterSizer.getMaxY()}
{
    _cell_size__px = calcCellSizePx(); // TODO check if too small. Maybe make an exception in print.
    _house_size__px = calcHouseSizePx();

    _x_axis_length__px = calcXAxisLengthPx();
    _y_axis_length__px = calcYAxisLengthPx();

    _cross_hairs_x__px = calcXCrossHairsPx();
    _cross_hairs_y__px = calcYCrossHairsPx();

    _pixel_converter_x = createPixelConverterX();
    _pixel_converter_y = createPixelConverterY();

    _house_min_x__px = _pixel_converter_x->getPixel(_house_min_x);
    _house_min_y__px = _pixel_converter_y->getPixel(_house_min_y);
    _house_max_x__px = _pixel_converter_x->getPixel(_house_max_x);
    _house_max_y__px = _pixel_converter_x->getPixel(_house_max_y);

    _title_x__px = _house_min_x__px + (_house_max_x__px - _house_min_x__px)/2;
    _title_y__px = _top_left_corner_y__px;

    addCityXAxis();
    addCityYAxis();
    addTitle();
}

GrCityPrinter::GrCityPrinter(
    Renderer* renderer,
    std::map<Coordinate, House*> coordToHouseMap,
    std::map<int, std::pair<Color, Color>> resColors,
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int xSpaceLengthPx,
    int ySpaceLengthPx,
    AxisFormat axisFormatX,
    AxisFormat axisFormatY,
    Letter titleLetter,
    int minX,
    int maxX,
    int minY,
    int maxY
    ) : _renderer{renderer},
        _coord_to_house_map{coordToHouseMap},
        _res_colors{resColors},
        _top_left_corner_x__px{topLeftCornerXPx},
        _top_left_corner_y__px{topLeftCornerYPx},
        _x_given_space__px{xSpaceLengthPx},
        _y_given_space__px{ySpaceLengthPx},
        _axis_format_X{axisFormatX},
        _axis_format_Y{axisFormatY},
        _title_letter{titleLetter},
        _house_min_x{minX},
        _house_max_x{maxX},
        _house_min_y{minY},
        _house_max_y{maxY}
{ 
    _cell_size__px = calcCellSizePx(); // TODO check if too small. Maybe make an exception in print.
    _house_size__px = calcHouseSizePx();

    _x_axis_length__px = calcXAxisLengthPx();
    _y_axis_length__px = calcYAxisLengthPx();

    _cross_hairs_x__px = calcXCrossHairsPx();
    _cross_hairs_y__px = calcYCrossHairsPx();

    _pixel_converter_x = createPixelConverterX();
    _pixel_converter_y = createPixelConverterY();

    _house_min_x__px = _pixel_converter_x->getPixel(_house_min_x);
    _house_min_y__px = _pixel_converter_y->getPixel(_house_min_y);
    _house_max_x__px = _pixel_converter_x->getPixel(_house_max_x);
    _house_max_y__px = _pixel_converter_x->getPixel(_house_max_y);

    _title_x__px = _house_min_x__px + (_house_max_x__px - _house_min_x__px)/2;
    _title_y__px = _top_left_corner_y__px;

    addCityXAxis();
    addCityYAxis();
    addTitle();
}

void GrCityPrinter::addCityXAxis()
{   
    int length__coord = _house_max_x - _house_min_x;
    _x_axis_utility = std::make_unique<XAxisL2R>(
        "xAxis",
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
        "yAxis",
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

void GrCityPrinter::addTitle()
{   
    // Place Title a little below top of map (divide by 20).
    _renderer->setTextFormats(
        {100, 100, 100, 100},
        {0xAA, 0xFF, 0xFF, 0xFF},
        _title_letter.fontSize());
    _renderer->renderText(_title_x__px, _title_y__px, "City Map", 4);
}


void GrCityPrinter::printCity(std::map<House*, Resident*> houseToResMap)
{  (void) houseToResMap; // TODO why do I have a (void) here?
    printTitle();
    printXAxis();
    printYAxis();
    printHouses(houseToResMap);
}

void GrCityPrinter::printTitle()
{
    _renderer->setTextFormats({100, 100, 100, 100},
                              {0xAA, 0xFF, 0xFF, 0xFF},
                              _title_letter.fontSize());
    _renderer->renderText(_title_x__px, _title_y__px, _main_title, 4);
}

void GrCityPrinter::printXAxis()
{
    _x_axis_utility->print(_renderer);
}

void GrCityPrinter::printYAxis()
{
    _y_axis_utility->print(_renderer);
}

void GrCityPrinter::printHouses( std::map<House *, Resident *> houseToResMap )
{   
    std::map<Color, std::vector<Coordinate>> coordsPerColor =
        createVectorsForEachColor(houseToResMap);
    for (auto const &colorToCoordVector : coordsPerColor)
    {
        _renderer->addBlocksByColor(
            _house_size__px,
            _house_size__px,
            colorToCoordVector.second,
            _the_color_infos[colorToCoordVector.first].rgba);
    }
}

std::map<Color, std::vector<Coordinate>> GrCityPrinter::createVectorsForEachColor(
    std::map<House *, Resident *> houseToResMap)
{
    std::map<Color, std::vector<Coordinate>> colorToCoordinatesMap = {};

    for (auto const &x : _coord_to_house_map)
    {
        Coordinate coord = x.first;
        House *house = x.second;
        Color colorKey;
        if (houseToResMap.count(house) == 0)
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
                colorKey = getUnhappyColor(res->getGroupNumber());
            else
                colorKey = getHappyColor(res->getGroupNumber());
        }
        if (colorToCoordinatesMap.count(colorKey) == 0) // TODO  c++ knows how to do this in one step
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
    return _res_colors.at(resGroup).first;
}

Color GrCityPrinter::getUnhappyColor (int resGroup)
{
    return _res_colors.at(resGroup).second;
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

int GrCityPrinter::calcXCrossHairsPx ()
{
    return _top_left_corner_x__px + _axis_format_Y.getHeightOfAxisPx();
}

int GrCityPrinter::calcYCrossHairsPx ()
{
    return _top_left_corner_y__px + 
           _title_letter.getHeightIncLSpace() + 
           _axis_format_X.getHeightOfAxisPx();
}

int GrCityPrinter::calcCellSizePx ()
{
    // X-direction
    int numHousesXDir = _house_max_x - _house_min_x + 1;
    int xAxisLengthForHouses = _x_given_space__px - 
                               _axis_format_Y.getHeightOfAxisPx() -
                               _axis_format_X.offsetPx() - 
                               _axis_format_X.overrunPx();

    int xCellSize = xAxisLengthForHouses / (numHousesXDir); 
    
    // Y-direction
    int numHousesYDir = _house_max_y - _house_min_y + 1;
    int yAxisLengthForHouses = _y_given_space__px - 
                               _title_letter.getHeightIncLSpace() -
                               _axis_format_X.getHeightOfAxisPx() -
                               _axis_format_Y.offsetPx() - 
                               _axis_format_Y.overrunPx();
    int yCellSize = yAxisLengthForHouses / (numHousesYDir);

    return std::min(xCellSize, yCellSize);
}

int GrCityPrinter::calcHouseSizePx ()
{
    if (_cell_size__px < 4)
        return 0;
    int initialHouseSize = _cell_size__px / 2;
    return ( (_cell_size__px - initialHouseSize ) % 2 == 0) ? 
        initialHouseSize : ( initialHouseSize + 1);
}

int GrCityPrinter::calcXAxisLengthPx ()
{
    return _axis_format_X.offsetPx() + 
           _cell_size__px * (_house_max_x - _house_min_x + 1) +
           _axis_format_X.overrunPx();
}

int GrCityPrinter::calcYAxisLengthPx ()
{
    return _axis_format_Y.offsetPx() + 
           _cell_size__px * (_house_max_y - _house_min_y + 1) +
           _axis_format_Y.overrunPx();
}

std::unique_ptr<PixelConverter> GrCityPrinter::createPixelConverterX()
{
    int maxXAxisPixel = 
        _cross_hairs_x__px + 
        _axis_format_X.offsetPx() + 
        _cell_size__px * (_house_max_x - _house_min_x) + 
        _axis_format_X.overrunPx();
    
    return std::make_unique<PixelConverter>(
        _house_min_x,
        _house_max_x,
        _cross_hairs_x__px + _axis_format_X.offsetPx(),
        maxXAxisPixel
    );
}

std::unique_ptr<PixelConverter> GrCityPrinter::createPixelConverterY()
{
    int maxYAxisPixel = 
        _cross_hairs_y__px + 
        _axis_format_Y.offsetPx() + 
        _cell_size__px * (_house_max_y - _house_min_y) + 
        _axis_format_Y.overrunPx();
    
    return std::make_unique<PixelConverter>(
        _house_min_y,
        _house_max_y,
        _cross_hairs_y__px + _axis_format_Y.offsetPx(),
        maxYAxisPixel
    );
}

