#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>

bool mapContains (std::map<Color, std::vector<Coordinate>> aMap, Color aKey);
bool mapContains (std::map<int, Resident*> aMap, int aKey);

Printer_Graphic::Printer_Graphic (
    const std::size_t screen_width,
    const std::size_t screen_height,
    const std::size_t grid_width, 
    const std::size_t grid_height
): _renderer{screen_width, screen_height, grid_width, grid_height},
   _keep_polling{true}
{
    for (ColorInfo colorInfo : _the_colors)
    {

        _rgba_per_color[colorInfo._my_color];
    }

}

void Printer_Graphic::printScreen ()
{
    _renderer.Render();
    //std::thread t1(&Renderer::poll, _renderer);
    _keep_polling = true;
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
        int address = x.second;
        Color colorKey;
        if (!mapContains(residentsPerAddress, address))
        {   
            // No resident has this address. So this house is empty.
            colorKey = Color::absent;
        }
        else
        {   
            Resident* res = residentsPerAddress[address];
            colorKey = res->getColor();
        }

        if (!mapContains(coordinatesPerColor, colorKey))
        {
            std::vector<Coordinate> newCoordinateVector = {};
            coordinatesPerColor[colorKey] = newCoordinateVector;
        }
        coordinatesPerColor[colorKey].push_back(coord);
        count ++;
    }
    
    _renderer.RenderCity(coordinatesPerColor, Coordinate{50, 50});
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

bool mapContains (std::map<Color, std::vector<Coordinate>> aMap, Color aKey)
{
    return aMap.count(aKey);
}

bool mapContains (std::map<int, Resident*> aMap, int aKey)
{
    return aMap.count(aKey);
}
