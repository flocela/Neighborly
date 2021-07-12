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
    City* cityPtr,
    std::vector<ColorInfo> colorInfos
):  _screen_width{screen_width},
    _screen_height{screen_height},
    _renderer{_screen_width, _screen_height},
    _color_infos{colorInfos}
{
    std::map<Color, std::vector<int>> rgbaPerColor;
    for (ColorInfo colorInfo : _the_color_Infos)
    {
        rgbaPerColor[colorInfo._my_color] = colorInfo.rgba;
    }
    
    initCityCoordinateInfo(cityPtr);
    Coordinate graphOrigin = Coordinate{10, 10};
    _graphic_city_printer = std::make_unique<GraphicCityPrinter>(
        &_renderer,
        graphOrigin,
        _coord_to_house_map,
        rgbaPerColor,
        _cell_size,
        _min_x_coord,
        _max_x_coord,
        _min_y_coord,
        _max_y_coord,
        _x_axis_offset,
        _y_axis_offset,
        _x_axis_overrun,
        _y_axis_overrun,
        _titles_at_left_offset,
        _titles_at_top_offset,
        _axis_font_size
    );
    initGridAndHouseSize ();
}

void Printer_Graphic::initCityCoordinateInfo(City* cityPtr)
{
    std::vector<House*> houses = cityPtr->getHouses();
    for (House* house : houses)
    {   
        Coordinate coord =  cityPtr->getCoordinate(house->_address);
        
        _coord_to_house_map[coord] = house;
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
    // city graph will take up half the screen width, divide space among houses.
    // Each house will be inside one cell. _cell_size and _house_size will be
    // even numbers to simplify the math so that each house will be easily 
    // centered inside one cell. // TODO not really necessary
    _cell_size = _screen_width/2/(std::max(deltaX, deltaY));

    if (_cell_size % 2 != 0)
        _cell_size++;
    if (_cell_size > 12)
        _cell_size = 12;
    if (_cell_size <= 3)
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

    // city graph will take up half the screen height, divide space
    // among houses. Each house will be in one cell. _cell_size and _house_size
    // will be even numbers so that the houses will be centered.
    _cell_size = _screen_width/2/(std::max(deltaX, deltaY));

    if (_cell_size % 2 != 0)
        _cell_size++;
    if (_cell_size > 12)
        _cell_size = 12;
    if (_cell_size <= 3)
        throw (
            "Can not print a city graph with so many houses. Maximum number of houses"
             " per side is 150."
        );
    
    _house_size = _cell_size/2;
}


void Printer_Graphic::print (
    std::map<House*, Resident*> residentPerHouse,
    int run,
    int totRuns,
    std::string title
)
{   (void) run;
    (void) totRuns;
    (void) title;
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
            break;
        }
    }
}

std::map<Color, std::vector<Coordinate>> Printer_Graphic::createVectorsForEachColor (
    std::map<House*, Resident*> residentPerHouse
)
{
    std::map<Color, std::vector<Coordinate>> coordinatePerColor ={};
    for (auto const& x : _coord_to_house_map)
    {
        Coordinate coord = x.first;
        House* house = x.second;

        Color colorKey;

        if (residentPerHouse.count(house) == 0)
        {   
            // No resident has this address. So this house is empty.
            colorKey = Color::absent;
        }
        else
        {   
            Resident* res = residentPerHouse[house];
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




