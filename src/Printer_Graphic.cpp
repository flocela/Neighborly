#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>
#include "XAxisL2RTop.h"
#include "YAxisT2B.h"
#include "GrCityPrinter.h"
#include "GrDiversityPrinter.h"
#include "GrHappinessPrinterSizer.h"



void Printer_Graphic::init (
    std::unordered_map<const House*, Coordinate > coordPerHouse,
    std::unordered_map<const House*, std::set<const House*>> neighbors,
    int numOfRuns, 
    std::string title
)
{   
    _coordinates_per_house = coordPerHouse;
    _renderer = std::make_unique<Renderer>(_screen_width__px, _screen_height__px);
    initWindowLengths();
    initWindowTitle(title);
    initCityMap();
    initRunCounter(numOfRuns);
    initDiversityPrinter(neighbors);
    initHappinessPrinter();
}

void Printer_Graphic::initCityMap () // TODO throw exception if city too large
{
    determineMinMaxHouseCoords();
    setCityPrinter();
}

void Printer_Graphic::determineMinMaxHouseCoords()
{
    // Determine the min and max house coordinates for x and y.
    for (auto& pair : _coordinates_per_house)
    {   // Coordinates are not in pixels! Think of them as the house number.
        Coordinate coord =  pair.second;
        //std::cout << "PrinterGraphic: (x, y): (" << coord->getX() << ", " << coord->getY() << ")" << std::endl; 
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

void Printer_Graphic::setCityPrinter ()
{ 
    int unitSize = cityPrinterCalculatePxPerUnit();
    int houseSize = unitSize/2;
    houseSize = (houseSize % 2 == 0) ? houseSize : (houseSize + 1);

    GrCityPrinterSizer cityPrinterSizer = 
        GrCityPrinterSizer (
            _x_space__px - ( 2 * _side_border__px),
            _city_y_space__px,
            _axis_format_X,
            _axis_format_Y,
            _chart_title_letter,
            _min_x_coord,
            _max_x_coord,
            _min_y_coord,
            _max_y_coord,
            houseSize,
            unitSize,
            unitSize,
            _x_offset_multiplier * houseSize,
            _x_overrun_multiplier * houseSize,
            true,
            _color_key_letter
        );
   
    _city_printer = std::make_unique<GrCityPrinter>(
        cityPrinterSizer,
        _renderer.get(),
        _coordinates_per_house,
        _colors,
        _side_border__px,
        _city_map_chart_top_left_y_coord__px
    );
}

int Printer_Graphic::cityPrinterCalculatePxPerUnit()
{
    // start and end offsets are the offset_multiplier times the dot_size__px.
    // approximate the start and end offsets as offset_multiplier times the cellSize.

    int allowableXAxisLengthPx = _x_space__px - _axis_format_Y.getAxisHeightPx();
    int numOfCellsX = 
        (_max_x_coord - _min_x_coord) +
        (_x_offset_multiplier + _y_offset_multiplier);
    int xCellSize = allowableXAxisLengthPx/numOfCellsX;

    int allowableYAxisLengthPx = 
        _city_y_space__px -
        _chart_title_letter.getHeightIncLSpace() -
        _axis_format_Y.getAxisHeightPx();
    int numOfCellsY = 
        (_max_y_coord - _min_y_coord) +
        (_x_offset_multiplier + _y_offset_multiplier);

    int yCellSize =  allowableYAxisLengthPx/numOfCellsY;

    int smallestCellSize = std::min(xCellSize, yCellSize);
    smallestCellSize = (smallestCellSize%2 == 0)? smallestCellSize : (smallestCellSize+1);

    return (smallestCellSize < 4) ? 4 : smallestCellSize;
}

void Printer_Graphic::setColors (std::unordered_map<int, Color> colors)
{
    _colors = colors;
}

void Printer_Graphic::initRunCounter (int numOfRuns)
{   
    _num_of_runs = numOfRuns;

    _run_counter_printer = std::make_unique<GrRunCPrinter>(
        _renderer.get(), 
        _side_border__px, 
        _run_counter_top_y__px,
        _x_space_length__px,
        _chart_title_letter.getHeightIncLSpace(),
        _chart_title_letter,
        _num_of_runs );
}


void Printer_Graphic::print (
    std::unordered_map<const House*, const Resident*> residentPerHouse,
    int run
)
{   
    std::unordered_map<const Resident*, const House*> housePerResident;
    std::vector<const Resident*> residents;
    for (auto pair : residentPerHouse)
    {
        if (pair.second != nullptr) // resident is not nullptr
        {
        housePerResident[pair.second] = pair.first;
        residents.push_back(pair.second);
        }
    }

    printWindowTitle();
    _city_printer->printCity(residentPerHouse);

    _run_counter_printer->print(run);

    _dvsty_printer->print(
        housePerResident,
        residentPerHouse,
        run,
        _renderer.get()
    );

    _happiness_printer->print(
        housePerResident,
        run,
        _renderer.get()
    );
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

void Printer_Graphic::initDiversityPrinter (
    std::unordered_map<const House*, std::set<const House*>> neighbors
)
{
    GrChartASizer divSizer(
        _x_space__px,
        (int)(_chart_y_space__px * _diversity_chart_y_axis_fraction),
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _color_key_letter,
        0, // x axis min value
        _num_of_runs,
        0, // y axis
        10, // TODO get largest number of possible neighbors from city
        20, // unitX
        20, // unitY
        _dot_size__px,
        _x_offset_multiplier * _dot_size__px,
        _x_overrun_multiplier * _dot_size__px,
        false
    );

    std::set<std::string> moods{"neutral"};
    _dvsty_printer = std::make_unique<GrDvstyPrinter> (
        divSizer,
        _colors,
        moods,
        _x_center__px + _inside_border__px,
        _div_chart_top_y__px,
        "Diversity, Average Number of Disparate Neighbors per Resident per Run",
        neighbors
    );
}

void Printer_Graphic::initHappinessPrinter ()
{   
    GrChartASizer divSizer(
        _x_space__px,
        (int)(_chart_y_space__px * _hap_chart_y_axis_fraction),
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _color_key_letter,
        0, // x axis min value
        _num_of_runs,
        0, // y axis min value
        100, // 
        20, // unit X
        5,
        _dot_size__px,
        _x_offset_multiplier * _dot_size__px,
        _x_overrun_multiplier * _dot_size__px,
        false
    );

    std::set<std::string> moods{"neutral"};
    _happiness_printer = std::make_unique<GrHapPrinter> (
        divSizer,
        _colors,
        moods,
        _x_center__px + _inside_border__px,
        _hap_chart_top_y__px,
        "Happiness, Average Happiness per Resident (shown as a percentage)"
    );

    _renderer->setColorToRed();
    std::vector<SDL_Rect> rects = {};

    SDL_Rect rect;
    rect.w  = 10;
    rect.h = ((int)(_chart_y_space__px * _hap_chart_y_axis_fraction));
    rect.x = _x_center__px;
    rect.y = _hap_chart_top_y__px;
    rects.push_back(rect);
    _renderer->fillBlocks(rects);
}

int Printer_Graphic::maxNumOfHousesX (int screenWidth__px)
{   (void)screenWidth__px;
    //TODO figure this out
    return 100;
}

int Printer_Graphic::maxNumOfHousesY (int screenWidth__px)
{
    (void)screenWidth__px;
    //TODO figure this out
    return 100;
}

void Printer_Graphic::initWindowTitle (std::string title)
{
    _window_title_x__px = _screen_width__px/2;//TODO make XSpacePx into an attribute
    _window_title_y__px = _top_border__px;
    _window_title_string = title;
}

void Printer_Graphic::printWindowTitle ()
{
    _renderer->setTextFormats({100, 100, 100, 100},
                              {0xAA, 0xFF, 0xFF, 0xFF},
                              _window_title.letterHeight());
    _renderer->renderText(_window_title_x__px, _window_title_y__px, _window_title_string, 1);
}

void Printer_Graphic::initWindowLengths ()
{
    _x_space_length__px = _screen_width__px - (2 * _side_border__px);
    _x_space__px =  (_screen_width__px/2) - _side_border__px - _inside_border__px;
    _x_center__px = _screen_width__px/2;

    _run_counter_top_y__px = _top_border__px + _window_title.getHeightIncLSpace();

    // MAP OF CITY HOUSES CHART // left column
    _city_y_space__px = 
        _screen_height__px -
        _top_border__px -
        _window_title.getHeightIncLSpace() -
        (2*_chart_title_letter.getHeightIncLSpace()) - // Runs counter and color key
        _bottom_border__px;

    // Color key for city map sits below run counter
    _color_key_for_city_map_top_y__px = 
        _run_counter_top_y__px +
        _chart_title_letter.getHeightIncLSpace(); // Run counter

    // City map sits below color key for city map
    _city_map_chart_top_left_y_coord__px = 
        _color_key_for_city_map_top_y__px +
        _chart_title_letter.getHeightIncLSpace(); // color key for city map
    

    // DIVERSITY CHART, HAPPINESS CHART
    _chart_y_space__px = 
        _screen_height__px -
        _top_border__px -
        _window_title.getHeightIncLSpace() -
        (2 *_chart_title_letter.getHeightIncLSpace()) - // Runs counter and color key
        _bottom_border__px -
        _space_between_charts__px;
    
    // Color key for diversity and happiness charts sits below run counter
    _color_key_for_div_and_hap_top_y__px =
        _top_border__px +
        _window_title.getHeightIncLSpace() +
        _chart_title_letter.getHeightIncLSpace(); // Run counter

    // Diversity chart sits below color key for Diversity and Happiness charts
    _div_chart_top_y__px = 
        _color_key_for_div_and_hap_top_y__px +
        _chart_title_letter.getHeightIncLSpace(); // color key for div and hap charts

    // Happiness chart sits below Diversity chart
    _hap_chart_top_y__px =
        _div_chart_top_y__px +
        (_chart_y_space__px * _diversity_chart_y_axis_fraction) +
        _space_between_charts__px;

}

