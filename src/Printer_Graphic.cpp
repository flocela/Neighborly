#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>


Printer_Graphic::Printer_Graphic (
    const std::size_t screen_width,
    const std::size_t screen_height,
    City* cityPtr
):  _screen_width{screen_width},
    _screen_height{screen_height},
    _renderer{_screen_width, _screen_height},
    _keep_polling{true}
{
    for (ColorInfo colorInfo : _the_colors)
    {

        _rgba_per_color[colorInfo._my_color];
    }

    initCityCoordinateInfo(cityPtr);
    Coordinate cityOrigin = Coordinate{10, 10};
    std::cout << "PrinterGraphic min_y: " << _min_y_coord << std::endl;
    _graphic_city_printer = std::make_unique<GraphicCityPrinter>(
        &_renderer,
        cityOrigin,
        _grid_size,
        _min_x_coord,
        _max_x_coord,
        _min_y_coord,
        _max_y_coord,
        40,
        40,
        10,
        10,
        240,
        80,
        20
    );
    initGridAndHouseSize ();
}

void Printer_Graphic::initCityCoordinateInfo(City* cityPtr)
{
    std::vector<int> addresses = cityPtr->getAddresses();
    for (int address : addresses)
    {   
        Coordinate coord =  cityPtr->getCoordinate(address);
        _housePerCoordinate[coord] = address;
        if (coord.getX() > _max_x_coord)
            _max_x_coord = coord.getX();
        if (coord.getX() < _min_x_coord)
            _min_x_coord = coord.getX();
        if (coord.getY() > _max_y_coord)
            _max_y_coord = coord.getY();
        if (coord.getY() < _min_y_coord)
            _min_y_coord = coord.getY();
    }
    _min_x_coord = 3;
    _min_y_coord = 9;

    int deltaX = _max_x_coord - _min_x_coord;
    int deltaY = _max_y_coord - _min_y_coord;
    // city graph will take up half the screen width, divide space
    // among houses. Each house will be in one grid. _grid_size and _house_size
    // will be even so that the houses will be centered. // TODO not really necessary
    _grid_size = _screen_width/2/(std::max(deltaX, deltaY));

    if (_grid_size % 2 != 0)
        _grid_size++;
    if (_grid_size > 12)
        _grid_size = 12;
    if (_grid_size <= 3)
        throw (
            "Can not print a city graph with so many houses. Maximum number of houses"
             " per side is 150."
        );
}

void Printer_Graphic::initGridAndHouseSize ()
{
    // lengths of city are deltaX and deltaY
    int deltaX = _max_x_coord - _min_x_coord;
    int deltaY = _max_y_coord - _min_y_coord;

    // city graph will take up half the screen width, divide space
    // among houses. Each house will be in one grid. _grid_size and _house_size
    // will be even so that the houses will be centered. // TODO not really necessary
    _grid_size = _screen_width/2/(std::max(deltaX, deltaY));

    if (_grid_size % 2 != 0)
        _grid_size++;
    if (_grid_size > 12)
        _grid_size = 12;
    if (_grid_size <= 3)
        throw (
            "Can not print a city graph with so many houses. Maximum number of houses"
             " per side is 150."
        );
    
    _house_size = _grid_size/2;
}


void Printer_Graphic::print (
    std::map<int, Resident*> residentPerHouse,
    int run,
    int totRuns,
    std::string title
)
{   (void) run;
    (void) totRuns;
    (void) title;
    (void) residentPerHouse;

    // Print city at top right corner of screen.
    // Allow 10 and 10 pixels for x and y borders.
    //Coordinate cityOrigin = Coordinate{10, 10};

    _renderer.startFrame();
    _graphic_city_printer->printCity();
    //addCityGridLines(cityOrigin);
    
    /*
    _renderer.AddTopLeftDotGraph(
        createVectorsForEachColor(residentPerHouse), 
        cityOrigin, 
        _grid_size, 
        _house_size,
        _min_x_coord,
        _max_x_coord,
        _min_y_coord,
        _max_y_coord,
        "City Residents");*/
    _renderer.endFrame();
} 

void Printer_Graphic::keepScreen()
{
    SDL_Event e;
    int counter = 0;
    while (SDL_WaitEvent(&e) != 0)
    {   
        counter ++;
        if (e.type == SDL_QUIT)
        {
            //_keep_polling = false;
            break;
        }
    }
}
void Printer_Graphic::printResidents(std::map<int, Resident*> addressPerResident,
                                     std::map<int, Coordinate> coordinatePerAddress,
                                     int run,
                                     int totRuns,
                           			 std::string title)
{
    //TODO use unused parameters
    addressPerResident = {};
    coordinatePerAddress = {};
    run++;
    totRuns++;
    std::string x = title + "x";
}

std::map<Color, std::vector<Coordinate>> Printer_Graphic::createVectorsForEachColor (
    std::map<int, Resident*> residentPerHouse
)
{
    std::map<Color, std::vector<Coordinate>> coordinatePerColor ={};
    for (auto const& x : _housePerCoordinate)
    {
        Coordinate coord = x.first;
        int address = x.second;

        Color colorKey;

        if (residentPerHouse.count(address) == 0)
        {   
            // No resident has this address. So this house is empty.
            colorKey = Color::absent;
        }
        else
        {   
            Resident* res = residentPerHouse[address];
            colorKey = res->getColor();
        }

        if (coordinatePerColor.count(colorKey) == 0) // TODO  c++ knows how to do this in one step
        {
            std::vector<Coordinate> newCoordinateVector = {};
            coordinatePerColor[colorKey] = newCoordinateVector;
        }
        coordinatePerColor[colorKey].push_back(coord);
    } 
    return coordinatePerColor;
}

void Printer_Graphic::addCityGridLines (Coordinate orig)
{
    (void) orig;
    //Coordinate xAxesCoord = Coordinate{orig.getX(), orig.getY() + x_axis_offset};
    //Coordinate yAxes = Coordinate{orig.getX(), orig.getY() + 10 * gridSize};
    //Coordinate cAxes = Coordinate{orig.getX(), orig.getY() +  9 * gridSize};
    
    //Coordinate titleCoord = Coordinate{
    //    orig.getX() + ((maxX - minX)/2) * gridSize, 
    //    orig.getY() + _title_offset };
    //char* title_arr = &title[0];
    //addTitle (titleCoord, title_arr, 20);

    //addCityXAxis(orig, 4, 2, 80, 240, 18);
    //addCityYAxis(orig, 4, 2, 80, 240);

    
    //addCityHouses(cAxes, gridSize, blockSize, coordinatesPerColor, colorMap);
    
}

void Printer_Graphic::addCityXAxis (
    Coordinate chartOrigin, // top left corner of entire chart, including titles
    int leftOffset,
    int xOverrun,
    int titlesAtTopOffset,
    int titlesAtLeftOffset,
    int fontSize
)
{   
    _renderer.setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        fontSize
    );
    int lineLength = _max_x_coord - _min_x_coord + leftOffset + xOverrun;
    // xAxisOrigPixel and yAxisOrigPixel is where x and y axes cross
    int xAxisOrigPixel = chartOrigin.getX() + titlesAtLeftOffset;
    int yAxisOrigPixel = chartOrigin.getY() + titlesAtTopOffset;

    _renderer.setColorToMedGrey();

    // Axis line
    SDL_Rect block;
    block.w = lineLength * _grid_size;
    block.h = 1;
    block.x = xAxisOrigPixel;
    block.y = yAxisOrigPixel;
    _renderer.fillBlock(block);

    // Axis ticks
    block.w = _grid_size/2;
    block.h = _grid_size;
    block.y = yAxisOrigPixel - _grid_size/2;

    // First tick is at _min_x_coord, which may not be at a tens value. 
    int minXPixel = xAxisOrigPixel + leftOffset * _grid_size;
    block.x = minXPixel - _grid_size/2;
    _renderer.fillBlock(block);

    // Rest of ticks. They start at the first tens value.
    int nextTick = 10 - (_min_x_coord % 10);
    block.x = minXPixel +  nextTick * _grid_size - _grid_size/2;
    int numOfBlocks = ( lineLength / 10 );
    _renderer.renderBlocksHorizontally(block, _grid_size * 10, numOfBlocks);

    _renderer.setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        fontSize
    );

    // number for first tick
    _renderer.renderText(minXPixel, block.y, std::to_string(_min_x_coord), 1);

    // number for second tick
    int nextNum = _min_x_coord + nextTick;
    _renderer.renderText(
        minXPixel + nextTick * _grid_size,
        block.y,
        std::to_string(nextNum),
        1
    );

    // numbers for rest of ticks
    int first50 = nextNum - (nextNum % 50) + 50;
    _renderer.renderNumbersHorizontally(
        minXPixel + (first50 - _min_x_coord) * _grid_size,
        block.y,
        first50,
        50,
        50 * _grid_size,
        (lineLength + _min_x_coord - first50)/50 + 1,
        1
    );
    
    SDL_Rect centerBlock;
    
    centerBlock.w = 2;
    centerBlock.h = 2;
    centerBlock.x = chartOrigin.getX();
    centerBlock.y = chartOrigin.getY();
    _renderer.fillBlock(centerBlock);
}

void Printer_Graphic::addCityYAxis (
    Coordinate graphOrigin,
    int topOffset,
    int yOverrun,
    int titlesAtTopOffset,
    int titlesAtRightOffset)
{
    _renderer.setColorToMedGrey();

    SDL_Rect block;

    block.w = 1;
    block.h = (_max_y_coord - _min_y_coord) * _grid_size + 
              (topOffset + yOverrun) * _grid_size;
    block.x = graphOrigin.getX() + titlesAtRightOffset;
    block.y = graphOrigin.getY() + titlesAtTopOffset;
    _renderer.fillBlock(block);
}




