#ifndef PRINTER_Graphic_H
#define PRINTER_Graphic_H

#include "Title.h"
#include "GrCityChart.h"
#include "Printer.h"
#include "renderer.h"
#include <thread>
#include <memory>
#include "House.h"
#include <vector>
#include "Color.h"
#include "GrRunsChart.h"
#include "GrColorKeyPrinter.h"
#include "Letter.h"
#include "GrDvstyChart.h"
#include "GrHapChart.h"
#include "GrChartASizer.h"

//  Displays CityMap, Diversity Chart, and HappinessChart.
//  Uses a screen width and height of 2400px.
class Printer_Graphic : public Printer
{   
public:
    Printer_Graphic (
        std::string title,
        std::unordered_map<int, BaseColor> colors,
        std::unordered_map<const House*, Coordinate > coordPerHouse,
        std::unordered_map<const House*, std::set<const House*>> neighbors,
        int numOfRuns
    );
    Printer_Graphic (const Printer_Graphic& obj) = default;
    Printer_Graphic (Printer_Graphic&& obj) noexcept = default;
    Printer_Graphic& operator= (const Printer_Graphic& obj) = default;
    Printer_Graphic& operator= (Printer_Graphic&& obj) noexcept = default;
    ~Printer_Graphic () = default;

    int maxNumOfHousesX (int screenWidth__px);
    int maxNumOfHousesY (int screenHeight__px);

    void print(
        std::unordered_map<const House*, const Resident*> residentPerHouse,
        int run
    ) override;

    void keepScreen();

private:
    
    std::unordered_map<const House*, Coordinate> _coordinates_per_house = {};
    std::unordered_map<int, BaseColor> _colors;
    int _num_of_types_of_residents = 2;

    /* FOR WINDOW */

    int _screen_width__px  = 2400;
    int _screen_height__px = 1200;
    std::unique_ptr<Renderer> _renderer = std::make_unique<Renderer>(
        _screen_width__px,
        _screen_height__px
    );

    int _top_border__px        = 10;
    int _bottom_border__px     = 10;
    int _left_right_borders__px = 20;

    // total x space minus the side borders
    int _x_space__px = _screen_width__px - (2 * _left_right_borders__px);

    // center of screen
    int _x_center__px = _screen_width__px/2;

    std::unique_ptr<Title> _window_title = std::make_unique<Title>(40, 2, _top_border__px, _x_center__px);


    /* COLUMNS */

    // Two columns: City Map chart is in the left. Diversity and Happiness charts are in the right.

    int _col_side_border__px = 10; 


    /* COMMON TO ALL CHARTS */

    int _text_width_multiplier = 0.3;
    int _num_of_runs;

    AxisFormat _axis_format_X{};
    AxisFormat _axis_format_Y{};

    // _used for Num Of Runs, City Map, Diversity...
    Letter _chart_title_letter = Letter(30, 6); 
    
    // space per chart in the x direction
    int _x_chart_space__px =  (_screen_width__px/2) - _left_right_borders__px - _col_side_border__px; 

    // At the start of the axis, leave a space of cell size or point size times offset.
    // At the end of the axis, leave a space of cell size or point size times overrun.
    const int _x_offset_multiplier  = 1;
    const int _x_overrun_multiplier = 1;
    const int _y_offset_multiplier  = 1;
    const int _y_overrun_multiplier = 1;

    // vertical space
    int _space_between_charts__px = 20;


    /* RUNS COUNTER */

    // Sits center, below window title
    int _runs_chart_top_y__px = _top_border__px + _window_title->sizeY();
    std::unique_ptr<GrRunsChart> _runs_chart = std::make_unique<GrRunsChart>(
        _left_right_borders__px, 
        _runs_chart_top_y__px,
        _x_space__px,
        _chart_title_letter.getHeightIncLSpace(),
        _chart_title_letter,
        _text_width_multiplier);


    /* RIGHT COLUMN */

    // Right column holds the diversity chart and happiness chart
    int _chart_y_space__px = 
        _screen_height__px -
        _top_border__px -
        _window_title->sizeY() -
        _chart_title_letter.getHeightIncLSpace() - // Runs chart
        _bottom_border__px -
        _space_between_charts__px;

    // Diversity and Happiness charts use the same _color_key_letter and _dot_size__px
    Letter _color_key_letter{24, 4};
    int _dot_size__px = 4;
    

    /* DIVERSITY CHART */

    // Diversity chart is the right column
    // Diversity chart sits below number of runs chart
    int _div_chart_top_y__px = _runs_chart_top_y__px + _chart_title_letter.getHeightIncLSpace();

    double _diversity_chart_y_axis_fraction = 0.3;

    int _max_number_of_neighbors = 12;
    
    GrChartASizer _div_sizer{
        _x_chart_space__px,
        ((int)(_chart_y_space__px * _diversity_chart_y_axis_fraction)),
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _color_key_letter,
        _dot_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier,
        true
    };
    
    std::unique_ptr<GrDvstyChart> _dvsty_chart;


    /* HAPPINESS CHART */

    // Happiness chart sits below Diversity chart
    int _hap_chart_top_y__px =
        _div_chart_top_y__px +
        (_chart_y_space__px * _diversity_chart_y_axis_fraction) +
        _space_between_charts__px;

    double _hap_chart_y_axis_fraction = 0.7;

    GrChartASizer _hap_sizer{
        _x_chart_space__px,
        ((int)(_chart_y_space__px * _hap_chart_y_axis_fraction)),
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _color_key_letter,
        _dot_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier,
        true
    };

    std::unique_ptr<GrHapChart> _happiness_chart;

    // COLOR KEY FOR DIVERSITY AND HAPPINESS CHARTS
    Letter _color_key_letter_for_map{24, 4}; // TODO is this used. Should be replace dby _color_key_letter

    std::vector<int> determineMinMaxHouseCoords (
        std::unordered_map<const House*, Coordinate > coordPerHouse
    );


    /* CITY MAP CHART */

    // City map chart is in the left column and sits below number of runs chart
    int _city_map_chart_top_left_y_coord__px = 
        _runs_chart_top_y__px +
        _chart_title_letter.getHeightIncLSpace(); // Number of Runs chart
    
    int _city_y_space__px = 
        _screen_height__px -
        _top_border__px -
        _window_title->sizeY() -
        _chart_title_letter.getHeightIncLSpace() - // Number of Runs Chart height // TODO get from chart not from letter given to chart
        _bottom_border__px;

    // Each house is inside of a square cell. The cell 
    // will hold a house (represented by a colored square) and have
    // clear border around the house.
    // difficult to see, if smaller than _smallest_allowable_cell_size__px
    int _smallest_allowable_cell_size__px = 4; 
    int _cell_size;  // pixels for square cell
    int _house_size; // pixels for colored square house

    std::unique_ptr<GrCityChart>  _city_chart;


    int determineMaxNumberOfNeighbors (
        std::unordered_map<const House*,
        std::set<const House*>> neighbors
    );

    std::unique_ptr<GrCityChart> createCityChart (
        int unitSize,
        int minXCoord, 
        int maxXCoord, 
        int minYCoord, 
        int maxYCoord);

    std::unique_ptr<GrDvstyChart> createDvstyChart(
        std::unordered_map<const House*, std::set<const House*>> neighbors,
        int maxNumOfNeighbors,
        int maxNumOfRuns
    );

    std::unique_ptr<GrHapChart> createHapChart (int numberOfRuns);

    int cityChartCalculatePxPerUnit(
        int minXCoord, 
        int maxXCoord, 
        int minYCoord, 
        int maxYCoord
    );
};

#endif