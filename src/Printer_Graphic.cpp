#include "Printer_Graphic.h"

#include <vector>
#include <map>
#include <utility>
#include <thread>
#include <chrono>
#include <iostream>
#include "XAxisL2RTop.h"
#include "YAxisT2B.h"

void Printer_Graphic::init (
    std::unordered_map<const House*, Coordinate > coordPerHouse,
    std::unordered_map<const House*, std::set<const House*>> neighbors,
    int numOfRuns,
    std::unordered_map<int, Color> colors,
    std::string title
)
{   
    _coordinates_per_house = coordPerHouse;
    _colors = colors;
    _renderer = std::make_unique<Renderer>(_screen_width__px, _screen_height__px);
    _num_of_runs = numOfRuns;
    initWindowLengths();
    initWindowTitle(title);
    initCityChart();
    initRunsChart();
    initDvstyChart(neighbors);
    initHapChart();
}

void Printer_Graphic::initCityChart () // TODO throw exception if city too large
{
    determineMinMaxHouseCoords();
    int pixelsPerHouseUnit = cityChartCalculatePxPerUnit();
    setCityChart(pixelsPerHouseUnit);
}

void Printer_Graphic::determineMinMaxHouseCoords()
{
    // Determine the min and max house coordinates for x and y.
    for (auto& pair : _coordinates_per_house)
    {
        Coordinate coord =  pair.second;
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

void Printer_Graphic::setCityChart (int unitSize)
{ 
    int houseSize = unitSize/2;
    houseSize =  ((unitSize - houseSize) % 2 == 0) ? houseSize : (houseSize + 1);

    GrCityChartSizer cityPrinterSizer = 
        GrCityChartSizer (
            _x_space__px,
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
            _x_offset_multiplier * houseSize,
            _x_overrun_multiplier * houseSize,
            true,
            _color_key_letter
        );
   
    _city_chart = std::make_unique<GrCityChart>(
        cityPrinterSizer,
        _renderer.get(),
        _coordinates_per_house,
        _colors,
        _side_border__px,
        _city_map_chart_top_left_y_coord__px
    );
}

int Printer_Graphic::cityChartCalculatePxPerUnit()
{
    // start and end offsets are the offset_multiplier times the dot_size__px.
    // approximate the start and end offsets as offset_multiplier times the cellSize.

    int allowableXAxisLengthPx = _x_space__px - _axis_format_Y.getAxisHeightPx();
    int numOfCellsX = 
        (_max_x_coord - _min_x_coord) +
        (_x_offset_multiplier + _x_overrun_multiplier);
    int xCellSize = allowableXAxisLengthPx/numOfCellsX;

    int allowableYAxisLengthPx = 
        _city_y_space__px -
        _chart_title_letter.getHeightIncLSpace() -
        _color_key_letter.getHeightIncLSpace() - 
        _axis_format_Y.getAxisHeightPx();

    int numOfCellsY = 
        (_max_y_coord - _min_y_coord) +
        (_y_offset_multiplier + _y_overrun_multiplier);

    int yCellSize =  allowableYAxisLengthPx/numOfCellsY;

    int smallestCellSize = std::min(xCellSize, yCellSize);
    
    // TODO what todo about smallest acceptable size??
    return (smallestCellSize < 4) ? 4 : smallestCellSize;
}

void Printer_Graphic::initRunsChart ()
{   
    _runs_chart = std::make_unique<GrRunsChart>(
        _renderer.get(), 
        _side_border__px, 
        _run_counter_top_y__px,
        _x_space_length__px,
        _chart_title_letter.getHeightIncLSpace(),
        _chart_title_letter,
        _num_of_runs );
}

void Printer_Graphic::initDvstyChart (
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
    _dvsty_chart = std::make_unique<GrDvstyChart> (
        divSizer,
        _colors,
        moods,
        _x_center__px + _inside_border__px,
        _div_chart_top_y__px,
        "Diversity, Average Number of Disparate Neighbors per Resident per Run",
        neighbors
    );
}

void Printer_Graphic::initHapChart ()
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
    _happiness_chart = std::make_unique<GrHapChart> (
        divSizer,
        _colors,
        moods,
        _x_center__px + _inside_border__px,
        _hap_chart_top_y__px,
        "Happiness, Average Happiness per Resident (shown as a percentage)"
    );
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
    _city_chart->printCity(residentPerHouse);

    _runs_chart->print(run);

    _dvsty_chart->print(
        housePerResident,
        residentPerHouse,
        run,
        _renderer.get()
    );

    _happiness_chart->print(
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

    // RUNS CHART centered below window title
    _run_counter_top_y__px = _top_border__px + _window_title.getHeightIncLSpace();

    // Left colulmn holds CITY CHART
    _city_y_space__px = 
        _screen_height__px -
        _top_border__px -
        _window_title.getHeightIncLSpace() -
        _chart_title_letter.getHeightIncLSpace() - // Runs chart
        _bottom_border__px;

    // City chart sits below runs counter chart
    _city_map_chart_top_left_y_coord__px = 
        _run_counter_top_y__px +
        _chart_title_letter.getHeightIncLSpace(); // Runs chart

    // Right column holds DIVERSITY CHART and HAPPINESS CHART
    _chart_y_space__px = 
        _screen_height__px -
        _top_border__px -
        _window_title.getHeightIncLSpace() -
        _chart_title_letter.getHeightIncLSpace() - // Runs chart
        _bottom_border__px -
        _space_between_charts__px;

    // Diversity chart sits below runs counter chart
    _div_chart_top_y__px = 
        _run_counter_top_y__px +
        _chart_title_letter.getHeightIncLSpace(); // Runs chart

    // Happiness chart sits below Diversity chart
    _hap_chart_top_y__px =
        _div_chart_top_y__px +
        (_chart_y_space__px * _diversity_chart_y_axis_fraction) +
        _space_between_charts__px;

}