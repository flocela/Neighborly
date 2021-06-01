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
    std::map<Color, std::vector<Coordinate>> coordinatesPerColor = {};
    int count = 0;
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
        if (coordinatesPerColor.count(colorKey) == 0)
        {
            std::vector<Coordinate> newCoordinateVector = {};
            coordinatesPerColor[colorKey] = newCoordinateVector;
        }
        coordinatesPerColor[colorKey].push_back(coord);
        count ++;
    }

    int deltaX = _max_x_coord - _min_x_coord;
    int deltaY = _max_y_coord - _min_y_coord;
    int tempGridWidth = _screen_width/2/deltaX;
    int tempGridHeight = _screen_width/2/deltaY;

    // if gridSize is less than 4, probably is going to look too small.
    int gridSize = std::min(tempGridHeight, tempGridWidth);
    Coordinate cityOrigin = Coordinate{
        static_cast<int>(_screen_width)/2 - 6*gridSize,
        16 * gridSize};
    int blockSize = gridSize/2;
    if ( (gridSize - blockSize) % 2 != 0)
        blockSize++;

    _renderer.startFrame();
    
    _renderer.AddCity(
        coordinatesPerColor, 
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

