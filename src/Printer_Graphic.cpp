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
    _city = cityPtr; // TODO make this const???
    initWindowValues();
    initWindowTitle(title);
    _renderer = std::make_unique<Renderer>(_screen_width__px, _screen_height__px);
    initCityMap(cityPtr);
    initRunCounter(numOfRuns);
    initDiversityPrinter();
    initHappinessPrinter();
    initColorKeyForCityMap();
    initColorKeyForDivAndHapCharts();
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
        GrCityPrinterSizer (_x_space__px,
                            _city_y_space__px,
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
        _side_border__px,
        _city_map_chart_top_left_y_coord__px
    );
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
    std::unordered_map<House*, Resident*> residentPerHouse,
    int run
)
{   
    //(void) residentPerHouse;
    //(void) run;
    std::unordered_map<Resident*, House*> housePerResident;
    std::vector<Resident*> residents;
    for (auto pair : residentPerHouse)
    {
        if (pair.second != nullptr) // resident is not nullptr
        {
        housePerResident[pair.second] = pair.first;
        residents.push_back(pair.second);
        }
    }

    printWindowTitle();
    //_city_printer->printCity(residentPerHouse);
    //_run_counter_printer->print(run);
    //_color_key_for_map_printer->print(_renderer.get());
    //_color_key_for_hap_and_div_printer->print(_renderer.get());
    _dvsty_printer->print(
        _city,
        housePerResident,
        residentPerHouse,
        run,
        _renderer.get()
    );
    //_diversity_printer->print(housePerResident, residents, _renderer.get());
    //_happiness_printer->print(housePerResident, residents, _renderer.get());
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

void Printer_Graphic::initColorKeyForCityMap ()
{
    std::set<std::string> moods{"happy", "unhappy"};
    _color_key_for_map_printer = std::make_unique<GrColorKeyPrinter>(
        _side_border__px,
        _top_border__px + _window_title.getHeightIncLSpace() + _chart_title_letter.getHeightIncLSpace(),
        _x_space__px,
        _color_key_letter,
        _colors,
        moods
    );
}

void Printer_Graphic::initColorKeyForDivAndHapCharts ()
{
    std::set<std::string> moods{"neutral"};
    _color_key_for_hap_and_div_printer = std::make_unique<GrColorKeyPrinter>(
        _x_center__px + _inside_border__px,
        _color_key_for_div_and_hap_top_y__px,
        _x_space__px,
        _color_key_letter,
        _colors,
        moods
    );
}

void Printer_Graphic::initDiversityPrinter ()
{
    /*GrDiversityPrinterSizer grDivPrinterSizer{
        _x_space__px,
        (int)(_chart_y_space__px * _diversity_chart_y_axis_fraction),
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        0,
        _num_of_runs
    };
    _diversity_printer = std::make_unique<GrDiversityPrinter> (
        grDivPrinterSizer,
        _colors,
        _x_center__px + _inside_border__px,
        _div_chart_top_y__px,
        0,
        10, // TODO get largest from city map
        "Diversity, Average Number of Disparate Neighbors per Resident per Run"
    );*/


    ////////

    GrChartASizer divSizer(
        _x_space__px,
        (int)(_chart_y_space__px * _diversity_chart_y_axis_fraction),
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _resident_keys,
        0, // x axis
        _num_of_runs,
        0, // y axis
        10, // TODO get largest number of possible neighbors from city
        1, // unitX
        20, // unitY
        4,
        _x_offset__px,
        _x_overrun__px,
        false
    );

    std::set<std::string> moods{"neutral"};
    _dvsty_printer = std::make_unique<GrDvstyPrinter> (
        divSizer,
        _colors,
        moods,
        _x_center__px + _inside_border__px,
        _div_chart_top_y__px,
        "Diversity, Average Number of Disparate Neighbors per Resident per Run"
    );



}

void Printer_Graphic::initHappinessPrinter ()
{
    GrDiversityPrinterSizer grHapPrinterSizer{
        _x_space__px,
        (int)(_chart_y_space__px * _hap_chart_y_axis_fraction),
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        0,
        _num_of_runs,
    };
    _happiness_printer = std::make_unique<GrDiversityPrinter> (
        grHapPrinterSizer,
        _colors,
        _x_center__px + _inside_border__px,
        _hap_chart_top_y__px,
        0,
        100,
        "Average Happiness per Group per Run"
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

