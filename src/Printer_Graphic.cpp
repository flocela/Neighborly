#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>
#include "XAxisUtility.h"


Printer_Graphic::Printer_Graphic (
    int maxNumOfRuns,
    const std::size_t screen_width,
    const std::size_t screen_height,
    City* cityPtr,
    std::set<Color> colors
):  _screen_width{screen_width},
    _screen_height{screen_height},
    _renderer{std::make_unique<Renderer>(_screen_width, _screen_height)},
    _colors{colors}
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
    XAxisUtility cityXAxisUtility(
        "xAxis",
        _renderer.get(),
        city_cross_hairs_x_px,
        city_cross_hairs_y_px,
        _cell_size,
        _min_x_coord,
        _max_x_coord,
        _city_x_axis_offset,
        _city_x_axis_overrun,
        10,
        12,
        12
    );
    cityXAxisUtility.left2RightTop();
    //_city_printer->printCity(residentPerHouse);
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
        Coordinate coord =  cityPtr->getCoordinate(house->getAddress());
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

    // Evenly divide houses among half the screen. 
    // Each house will be surrounded by a border and be inside one cell. 
    int deltaX = _max_x_coord - _min_x_coord;
    int deltaY = _max_y_coord - _min_y_coord;
    _cell_size = _screen_width/2/(std::max(deltaX, deltaY));

    // _cell_size will be even to simplify the math.
    _cell_size = (_cell_size % 2 != 0) ? _cell_size -1 : _cell_size;

    // Limit _cell_size so the squares don't appear to big (personal aesthetics).
    _cell_size = (_cell_size > 20) ? 20 : _cell_size;

    // Limit _cell_size. Cells required to be 4 pixels at least or too small to see.
    if (_cell_size <= 3)
        throw (
            "Can not print a city graph with so many houses. Maximum number of houses"
             " per side is 150."
        );

    _house_size = _cell_size/2;

    // _cell_size will be even to simplify the math.
    if (_house_size % 2 != 0)
        _house_size++;
}

void Printer_Graphic::initCityPrinter (Coordinate graphOrigin)
{
    std::set<Color> sadAndHappyColors;
    for (Color color : _colors)
    {
        sadAndHappyColors.insert(color);
        sadAndHappyColors.insert(_unhappy_color_map[color]);
    }
    _city_printer = std::make_unique<GraphicCityPrinter>(
        _renderer.get(),
        _coord_to_house_map,
        graphOrigin,
        sadAndHappyColors,
        _cell_size,
        _min_x_coord,
        _max_x_coord,
        _min_y_coord,
        _max_y_coord,
        _city_x_axis_offset,
        _city_y_axis_offset,
        _city_x_axis_overrun,
        _city_y_axis_overrun,
        240,
        80,
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