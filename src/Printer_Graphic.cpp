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
    initGridAndHouseSize ();
    _renderer.setGridWidthAndHeight(_grid_size, _grid_size);
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
}

void Printer_Graphic::initGridAndHouseSize ()
{
    // lengths of city are deltaX and deltaY
    int deltaX = _max_x_coord - _min_x_coord;
    int deltaY = _max_y_coord - _min_y_coord;

    // city graph will take up half the screen width, divide space
    // among houses. Each house will be in one grid.
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
{  
    run++;
    totRuns++;
    std::string x = title + "x"; // TODO used unused parameters.

    Coordinate cityOrigin = Coordinate{static_cast<int>(_screen_width)/2, 0};
    std::vector<Resident*> residentPtrs;
    for (auto &s : residentPerHouse)
    {
        residentPtrs.push_back(s.second);
    }

    _renderer.startFrame();
    
    _renderer.AddCity(
        createVectorsForEachColor(residentPerHouse), 
        cityOrigin, 
        _grid_size, 
        _house_size,
        _min_x_coord,
        _max_x_coord,
        _min_y_coord,
        _max_y_coord);
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
        int address = x.second;
        Coordinate coord = x.first;
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
        if (coordinatePerColor.count(colorKey) == 0)
        {
            std::vector<Coordinate> newCoordinateVector = {};
            coordinatePerColor[colorKey] = newCoordinateVector;
        }
        coordinatePerColor[colorKey].push_back(coord);
    } 
    return coordinatePerColor;
}

