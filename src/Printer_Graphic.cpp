#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>
#include "XAxisUtility.h"
#include "YDownAxisUtility.h"
#include "GraphicCityPrinterBuilder.h"
#include "GraphicCityPrinter.h"

// Shows a City Map Chart, the current run number, 
// a Happiness Chart, and a Diversity Chart.
// The Window Title and current run number will take up 100 pixels at top.
// The bottom border will take 20 pixels at the bottom.
// The writable vertical length = _screen_height - 80 - 20 pixels.
// Allow 0.4 of the writable vertical length for the City Map Chart.
// Allow 0.3 of the writable vertical length for the Happiness Chart.
// Allow 0.3 of the writable vertical length for the Diversity Chart.
// The left and right borders are 10 px. So,
// the writable horizontal length = _screen_width - 20 pixels.
Printer_Graphic::Printer_Graphic (
    int maxNumOfRuns,
    const int screen_width,
    const int screen_height,
    City* cityPtr,
    std::set<Color> colors
):  _screen_width{screen_width},
    _screen_height{screen_height},
    _writable_horiz_length__px{_screen_width - _left_border__px - _right_border__px},
    _writable_vert_length__px{_screen_height - _window_title__px - _bottom_border__px},
    _map_writable_vert_length__px{_writable_vert_length__px * 6 / 10},
    _hapiness_chart_writable_vert_length__px{_writable_vert_length__px * 3 / 10},
    _diversity_chart_writable_vert_length__px{
        _writable_vert_length__px - 
        _map_writable_vert_length__px - 
        _hapiness_chart_writable_vert_length__px},
    _renderer{std::make_unique<Renderer>(_screen_width, _screen_height)},
    _colors{colors}
{
    initCityInfo(cityPtr);
    initCityMapInfo();
    Coordinate graphOrigin = Coordinate{10, 10};
    initCityPrinter(graphOrigin);
    initRunCounterPrinter(maxNumOfRuns);
    initDiversityPrinter();
}

void Printer_Graphic::print (
    std::map<House*, Resident*> residentPerHouse,
    int run,
    std::string title
)
{   
    (void) title;
    (void) residentPerHouse;
    (void) run;
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

void Printer_Graphic::initCityInfo(City* cityPtr)
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
}

void Printer_Graphic::initCityMapInfo ()
{
    // Find _cell_size. Each cell contains a house surrounded by a border.
    // 
    // Limits:
    // Smallest allowable cell size is 4, otherwise I can't see the house.
    // Largest allowable cell size is 20, otherwise looks too big.
    // Limits for the x axis:
    //   // I have a _writable_horizontal_length. 
    //   // I am using a GraphicCityPrinter, which uses 300px on the left side.
    //   // The xAxisLength will be writable_horizontal_length - 300px.
    //   // The allowable length for the houses will be the
    //   // xAxisLength - _city_x_axis_offset__px - _city_x_axis_overrun__px.
    //   // The _cell_size = allowableHousesLengthX / (_max_x_coord - _min_x_coord),
    //   // where the max and min coordinates coorespond to the most 
    //   // right and left houses.
    // Limits for the y axis:
    //   // I have a _writable_vertical_length.
    //   // I am using a GraphicalCityPrinter, which uses 80px above the y-axis.
    //   // The yAxisLength will be the _writable_vertical_length - 80px.
    //   // The allowable length for the houses will be the
    //   // yAxisLength - _city_y_axis_offset__px - _city_y_axis_overrun__px.
    //   // The _cell_size = allowableHouseLengthY / (_max_y_coord - _min_y_coord),
    //   // where teh max and min coordinates correspond to the most 
    //   // bottom and top houses.
    // GraphicCityPrinter uses a square cell size, take smaller of
    // axes' cell sizes.


    int deltaX = _max_x_coord - _min_x_coord;
    int xAxisLength = _writable_horiz_length__px - 300;
    int allowableHousesLengthX = 
        xAxisLength - _city_x_axis_offset__px - _city_x_axis_overrun__px;
    int xCellSize = allowableHousesLengthX / deltaX;
    
    int deltaY = _max_y_coord - _min_y_coord;
    int yAxisLength = _map_writable_vert_length__px - 80;
    int allowableHousesLengthY =
        yAxisLength - _city_y_axis_offset__px - _city_y_axis_overrun__px;
    int yCellSize = allowableHousesLengthY / deltaY;

    _cell_size = std::min(xCellSize, yCellSize);
    // Limit _cell_size. Cells required to be 4 pixels at least or too small to see.
    if (_cell_size < 4)
    {
        throw (
            "Can not print a city graph with so many houses. Maximum number of houses"
             " per side is 150."
        );
    }

    // Limit _cell_size so the squares don't appear to big.
    _cell_size = (_cell_size > 20) ? 20 : _cell_size;
    
    // House must be at center of cell. // TODO may not need _house_size
    _house_size = (_cell_size % 2 == 0) ? (_cell_size/2) : ( (_cell_size/2) + 1);

    _city_tick_spacing_x = findTickSpacing(deltaX);
    _city_label_spacing_x = findLabelSpacing(deltaX);
    _city_tick_spacing_y = findTickSpacing(deltaY);
    _city_label_spacing_y = findLabelSpacing(deltaY);

    _city_cross_hairs_x__px = _left_border__px + 300;
    _city_cross_hairs_y__px = _window_title__px + 80;

}

void Printer_Graphic::initCityPrinter (Coordinate graphOrigin)
{ (void) graphOrigin;
    std::set<Color> sadAndHappyColors;
    for (Color color : _colors)
    {
        sadAndHappyColors.insert(color);
        sadAndHappyColors.insert(_unhappy_color_map[color]);
    }
    GraphicCityPrinterBuilder builder = GraphicCityPrinterBuilder();
    builder.addRenderer(_renderer.get())
    .addCoordinateToHouseMap(_coord_to_house_map)
    .addCrossHairsCoordinate(Coordinate{_city_cross_hairs_x__px, _city_cross_hairs_y__px})
    .addCellSize(_cell_size)
    .addXAxisTickSpacing(_city_tick_spacing_x)
    .addYAxisTickSpacing(_city_tick_spacing_y)
    .addAxesWidthInPixels(_city_axis_width__px)
    .addXAxisLabelSpacing(_city_label_spacing_x)
    .addYAxisLabelSpacing(_city_label_spacing_y)
    .addMinimumXValueForHouse(_min_x_coord)
    .addMaximumXValueForHouse(_max_x_coord)
    .addMinimumYValueForHouse(_min_y_coord)
    .addMaximumYValueForHouse(_max_y_coord)
    .addXAxisOffsetInPixels(_city_x_axis_offset__px)
    .addYAxisOffsetInPixels(_city_y_axis_offset__px)
    .addXAxisOverrunInPixels(_city_x_axis_overrun__px)
    .addYAxisOverrunInPixels(_city_y_axis_overrun__px)
    .addFontSizeForTickLabels(_axis_label_font_size)
    .addFontSizeForKeyLabels(_key_font_size)
    .addFontSizeForTitle(_sub_title_font_size);
    _city_printer = builder.build();
    /*_city_printer = std::make_unique<GraphicCityPrinter>(
        _renderer.get(),
        _coord_to_house_map,
        _city_cross_hairs_x__px,
        _city_cross_hairs_y__px,
        sadAndHappyColors,
        _cell_size,
        _city_tick_spacing_x,
        _city_tick_spacing_y,
        _city_tick_width__px, // TODO must add this method for tick width__px
        _city_axis_width__px,
        _city_label_spacing_x,
        _city_label_spacing_y,
        _min_x_coord,
        _max_x_coord,
        _min_y_coord,
        _max_y_coord,
        _city_x_axis_offset__px,
        _city_y_axis_offset__px,
        _city_x_axis_overrun__px,
        _city_y_axis_overrun__px,
        _axis_label_font_size,
        _key_font_size,
        _sub_title_font_size
    );*/
}

void Printer_Graphic::initRunCounterPrinter (int maxNumOfRuns)
{
    _run_counter_printer = std::make_unique<GraphicRunCounterPrinter>(
        _renderer.get(), 
        _x_num_of_runs_offset, 
        _y_num_of_runs_offset,
        maxNumOfRuns );
}

void Printer_Graphic::initDiversityPrinter ()
{
    _diversity_printer = std::make_unique<GraphicDiversityPrinter> (
        _renderer.get(),
        _colors,
        _diversity_chart_writable_vert_length__px,
        _writable_horiz_length__px - 300, // same -300 used for CityPrinter. Make this a variable
        _left_border__px + 300, // same -300 used for CityPrinter. Make this a variable
        _window_title__px + 80 + _map_writable_vert_length__px + _diversity_chart_writable_vert_length__px, // TODO how did I come up with this number
        _max_num_of_runs,
        3, // blocks will be 3 pixels wide and high. Make this into a variable.
        1, //border
        3, //block spacing
        3,
        1, // run spacing
        1,
        2,
        2,
        10,
        10,
        0,
        0,
        0,
        0,
        12,
        12,
        12
    );
}

int Printer_Graphic::findTickSpacing (int stretch)
{
    return (stretch <= 100)? 1 : 5;
}

int Printer_Graphic::findLabelSpacing (int stretch)
{
    return (stretch <= 10)? 1 : 10;
}

