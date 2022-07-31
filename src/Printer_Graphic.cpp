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

// Shows a City Map, the current run number, 
// a Happiness Chart, and a Diversity Chart.
// The Window Title and current run number will take up 100 pixels at top.
// The bottom border will take 20 pixels at the bottom.
// The writable vertical length = _screen_height - Window Title - bottom border.
// Allow 0.4 of the writable vertical length for the City Map Chart.
// Allow 0.3 of the writable vertical length for the Happiness Chart.
// Allow 0.3 of the writable vertical length for the Diversity Chart.
// The left and right borders are 10 px. So,
// the writable horizontal length = _screen_width - left border - right border.
Printer_Graphic::Printer_Graphic ( // TODO check if parameters are zero, if stop
    const int screen_width, // TODO screen_width and screen_height do not have to be const
    const int screen_height
):  _screen_width__px{screen_width},
    _screen_height__px{screen_height}
{}

void Printer_Graphic::init (City* cityPtr, int numOfRuns, std::string title)
{   
    initWindowValues();
    initWindowTitle(title);
    initAxesValues();
    _renderer = std::make_unique<Renderer>(_screen_width__px, _screen_height__px);
    initCityMap(cityPtr);
    initRunCounter(numOfRuns);
    initDiversityPrinter();
    initColorPrinter();
}

void Printer_Graphic::initAxesValues ()
{
    _city_map_chart_top_left_y_coord__px = calcCityMapChartTopLeftYCoordPx();
    _div_chart_y_top_left_y_coord__px = calcDivChartTopLeftYCoordPx();
}

void Printer_Graphic::initCityMap (City* cityPtr) // TODO throw exception if city too large
{
    determineMinMaxHouseCoords(cityPtr);
    setCityPrinter();
}

void Printer_Graphic::determineMinMaxHouseCoords(City* cityPtr)
{
    // Determine the min and max house coordinates for x and y.
    std::vector<House*> houses = cityPtr->getHouses();
    for (House* house : houses)
    {   // Coordinates are not in pixels! Think of them as the house number.
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

void Printer_Graphic::setCityPrinter ()
{ 
    GrCityPrinterSizer cityPrinterSizer = 
        GrCityPrinterSizer (_x_space_length__px,
                            _sum_y_space_lengths__px * _city_map_y_axis_fraction, // this has to become a function. this calc is done in two places in this class.
                            _axis_format_X,
                            _axis_format_Y,
                            _chart_title_letter,
                            _min_x_coord,
                            _max_x_coord,
                            _min_y_coord,
                            _max_y_coord
        );
    _city_printer = std::make_unique<GrCityPrinter>(
        cityPrinterSizer,
        _renderer.get(),
        _coord_to_house_map,
        _colors,
        _charts_top_left_x_coord__px,
        _city_map_chart_top_left_y_coord__px
    );
}

void Printer_Graphic::setColors (std::map<int,std::pair<Color, Color>> colors)
{
    _colors = colors;
}

void Printer_Graphic::initRunCounter (int numOfRuns)
{
    _num_of_runs = numOfRuns;
    _runs_chart_top_left_y__coord__px = 
        _top_border__px + _window_title.getHeightIncLSpace();

    _run_counter_printer = std::make_unique<GrRunCPrinter>(
        _renderer.get(), 
        _left_border__px, 
        _runs_chart_top_left_y__coord__px,
        _x_space_length__px,
        static_cast<int>(_sum_y_space_lengths__px * _diversity_chart_y_axis_fraction),
        _chart_title_letter,
        _num_of_runs );
}


void Printer_Graphic::print (
    std::map<House*, Resident*> residentPerHouse,
    int run
)
{   
    printWindowTitle();
    std::unordered_map<int,std::vector<int>> numOfLikeDiffPerGroup;
    (void) residentPerHouse;
    //_city_printer->printCity(residentPerHouse);
    _run_counter_printer->print(run);
    _color_printer->print(_renderer.get());
    _diversity_printer->print(numOfLikeDiffPerGroup, _renderer.get());
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

void Printer_Graphic::initColorPrinter ()
{
    _color_printer = std::make_unique<GrColorPrinter>(
        _charts_top_left_x_coord__px,
        _top_border__px + _window_title.getHeightIncLSpace() + _chart_title_letter.getHeightIncLSpace(),
        _x_space_length__px,
        _group_color_letter,
        _colors
    );
}

void Printer_Graphic::initDiversityPrinter ()
{
    GrDiversityPrinterSizer grDivPrinterSizer{
        _x_space_length__px,
        static_cast<int>(_sum_y_space_lengths__px * _diversity_chart_y_axis_fraction),
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        0,
        _num_of_runs
    };
    _diversity_printer = std::make_unique<GrDiversityPrinter> (
        grDivPrinterSizer,
        _colors,
        _charts_top_left_x_coord__px,
        calcDivChartTopLeftYCoordPx(),
        10 // TODO get largest from city map
    );
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

int Printer_Graphic::calcSumOfYSpacesPx ()
{
    return _screen_height__px -
           _top_border__px -
           _window_title.letterHeight() -
           _window_title.lineSpace() -
           _chart_title_letter.letterHeight() - // num of runs chart title
           _chart_title_letter.lineSpace() -
           _num_of_types_of_residents * _resident_keys.getHeightIncLSpace() -
           _bottom_border__px; 
}

int Printer_Graphic::calcXSpacePx ()
{
    return _screen_width__px -
           _left_border__px -
           _right_border__px;
}

int Printer_Graphic::calcLeftXCoordPx ()
{
    return _left_border__px;
}

int Printer_Graphic::calcCityMapChartTopLeftYCoordPx ()
{
    return _top_border__px +
           _window_title.getHeightIncLSpace() +
           ( 2 * _chart_title_letter.getHeightIncLSpace() );// Run counter chart plus Resident colors
}

int Printer_Graphic::calcDivChartTopLeftYCoordPx ()
{
    return _city_map_chart_top_left_y_coord__px + 
           (_sum_y_space_lengths__px * _city_map_y_axis_fraction);
}

int Printer_Graphic::calcRunChartTopLeftYCoordPx ()
{
    return _top_border__px + _window_title.getHeightIncLSpace();
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

void Printer_Graphic::initWindowValues ()
{
    _charts_top_left_x_coord__px = calcLeftXCoordPx();
    // all charts have the same _x_space_length__px
    _x_space_length__px = calcXSpacePx();
    // _sum_y_space_lengths__px is all three charts' y-direction spaces added up
    _sum_y_space_lengths__px = calcSumOfYSpacesPx ();
}

