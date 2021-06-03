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
    const std::size_t grid_width, 
    const std::size_t grid_height
):  _screen_width{screen_width},
    _screen_height{screen_height}, 
    _renderer{screen_width, screen_height, grid_width, grid_height},
    _keep_polling{true}
{
    for (ColorInfo colorInfo : _the_colors)
    {

        _rgba_per_color[colorInfo._my_color];
    }

}

void Printer_Graphic::print (
    std::map<int, Resident*> residentsPerAddress, 
    std::map<Coordinate, int> addressPerCoordinate,
    int run,
    int totalRuns,
    std::string title
)
{  
    run++;
    totalRuns++;
    std::string x = title + "x"; // TODO used unused parameters.
    printSetUp(residentsPerAddress, addressPerCoordinate);

    // lengths of city are deltaX and deltaY
    int deltaX = _max_x_coord - _min_x_coord;
    int deltaY = _max_y_coord - _min_y_coord;

    // city graph will take up half the screen width, divide space
    // among houses. Each house will be in one grid.
    int gridSize = _screen_width/2/(std::max(deltaX, deltaY));

    if (gridSize % 2 != 0)
        gridSize++;
    if (gridSize > 12)
        gridSize = 12;
    if (gridSize <= 3)
        throw (
            "Can not print a city graph with so many houses. Maximum number of houses"
             " per side is 150."
        );

    Coordinate cityOrigin = Coordinate{static_cast<int>(_screen_width)/2, 0};
    int blockSize = gridSize/2;
    if ( (gridSize - blockSize) % 2 != 0)
        blockSize++;

    _renderer.startFrame();
    
    _renderer.AddCity(
        _coordinatesPerColor, 
        cityOrigin, 
        gridSize, 
        blockSize,
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

void Printer_Graphic::cityCoordinateSetup (
    std::map<int, Resident*> residentsPerAddress, 
    std::map<Coordinate, int> addressPerCoordinate
)
{
   for (auto const& x : addressPerCoordinate)
    {
        Coordinate coord = x.first;
        if (coord.getX() > _max_x_coord)
            _max_x_coord = coord.getX();
        if (coord.getX() < _min_x_coord)
            _min_x_coord = coord.getX();
        if (coord.getY() > _max_y_coord)
            _max_y_coord = coord.getY();
        if (coord.getY() < _min_y_coord)
            _min_y_coord = coord.getY();

        int address = x.second;
        Color colorKey;
        //if (!mapContains(residentsPerAddress, address))
        if (residentsPerAddress.count(address) == 0)
        {   
            // No resident has this address. So this house is empty.
            colorKey = Color::absent;
        }
        else
        {   
            Resident* res = residentsPerAddress[address];
            colorKey = res->getColor();
        }
        if (_coordinatesPerColor.count(colorKey) == 0)
        {
            std::vector<Coordinate> newCoordinateVector = {};
            _coordinatesPerColor[colorKey] = newCoordinateVector;
        }
        _coordinatesPerColor[colorKey].push_back(coord);
    } 
}

