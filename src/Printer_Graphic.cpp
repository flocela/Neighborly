#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>


Printer_Graphic::Printer_Graphic (
    int maxNumOfRuns,
    const std::size_t screen_width,
    const std::size_t screen_height,
    City* cityPtr,
    std::vector<ColorInfo> colorInfos
):  _screen_width{screen_width},
    _screen_height{screen_height},
    _renderer{std::make_unique<Renderer>(_screen_width, _screen_height)},
    _color_infos{colorInfos}
{
    initCityCoordinateInfo(cityPtr);
    Coordinate graphOrigin = Coordinate{10, 10};
    initCityPrinter(graphOrigin);
    initRunCounterPrinter(maxNumOfRuns);
}

void Printer_Graphic::print (
    std::map<House*, Resident*> residentPerHouse,
    int run,
    std::string title
)
{   
    (void) title;
    (void) residentPerHouse;
    _city_printer->printCity(residentPerHouse);
    _run_counter_printer->print(run);
    _renderer->endFrame();
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

    // The city graph will take up half the screen width, so evenly divide space
    // among houses. Each house will be inside one cell. 
    // Also _cell_size and _house_size will be even numbers to simplify the math
    // so that each house will be easily centered inside one cell.
    int deltaX = _max_x_coord - _min_x_coord;
    int deltaY = _max_y_coord - _min_y_coord;
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

void Printer_Graphic::initCityPrinter (Coordinate graphOrigin)
{
    std::map<Color, std::vector<int>> rgbaPerColor;
    for (ColorInfo colorInfo : _the_color_Infos)
    {
        rgbaPerColor[colorInfo._my_color] = colorInfo.rgba;
    }

    _city_printer = std::make_unique<GraphicCityPrinter>(
        _renderer.get(),
        _coord_to_house_map,
        rgbaPerColor,
        graphOrigin,
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
}

void Printer_Graphic::initRunCounterPrinter (int maxNumOfRuns)
{
    _run_counter_printer = std::make_unique<GraphicRunCounterPrinter>(
        _renderer.get(), 
        _x_num_of_runs_offset, 
        _y_num_of_runs_offset,
        maxNumOfRuns );
}