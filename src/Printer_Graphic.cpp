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

        _rgba_per_color[colorInfo._my_color] = colorInfo.rgba;
    }
    
    initCityCoordinateInfo(cityPtr);
    Coordinate graphOrigin = Coordinate{10, 10};
    _graphic_city_printer = std::make_unique<GraphicCityPrinter>(
        &_renderer,
        graphOrigin,
        _coord_to_house,
        _rgba_per_color,
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
        _coord_to_house[coord] = address;
        if (coord.getX() > _max_x_coord)
            _max_x_coord = coord.getX();
        if (coord.getX() < _min_x_coord)
            _min_x_coord = coord.getX();
        if (coord.getY() > _max_y_coord)
            _max_y_coord = coord.getY();
        if (coord.getY() < _min_y_coord)
            _min_y_coord = coord.getY();
    }

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

    // Print city at top right corner of screen.
    // Allow 10 and 10 pixels for x and y borders.
    //Coordinate cityOrigin = Coordinate{10, 10};

    _renderer.startFrame();
    _graphic_city_printer->printCity(residentPerHouse);
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
    for (auto const& x : _coord_to_house)
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




