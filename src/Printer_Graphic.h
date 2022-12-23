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
#include "PlotSizer.h"
#include "TitleA.h"

//  Displays CityMap, Diversity Chart, and HappinessChart.
//  Uses a screen width and height of 2400px.
class Printer_Graphic : public Printer
{   
public:
    Printer_Graphic (
        std::string title,
        std::unordered_map<int, BaseColor> colors,
        std::unordered_map<const House*, Coordinate > coordPerHouse,
        std::unordered_map<const House*, std::set<const House*>> neighborHouses,
        int numOfRuns
    );
    Printer_Graphic (const Printer_Graphic& obj) = default;
    Printer_Graphic (Printer_Graphic&& obj) noexcept = default;
    Printer_Graphic& operator= (const Printer_Graphic& obj) = default;
    Printer_Graphic& operator= (Printer_Graphic&& obj) noexcept = default;
    ~Printer_Graphic () = default;

    int maxNumOfHousesX () {return 100;}
    int maxNumOfHousesY () {return 100;}
    int maxNumOfNeighbors () {return 12;}
    int maxNumOfResidentTypes () {return 2;}
    int maxNumOfRuns () { return 100;}

    void print(
        std::unordered_map<const House*, const Resident*> residentPerHouse,
        int run
    ) override;

    void keepScreen();

private:
    
    /* FOR WINDOW */
    int _screen_width__px  = 2400;
    int _screen_height__px = 1200;
    std::unordered_map<int, BaseColor> _colors;
    std::unordered_map<const House*, Coordinate> _coordinates_per_house = {};
    std::unique_ptr<Renderer> _renderer = std::make_unique<Renderer>(
        _screen_width__px,
        _screen_height__px
    );

    int _top_border__px = 20;
    int _bottom_border__px = 20;
    int _side_borders__px = 40; // both the left and right borders are this value
    int _col_inside_border__px = 40;
    int _x_center__px = _screen_width__px/2; // center of screen
    int _num_of_runs;

    Letter _window_title_letter{40, 2, 0.3};
    std::unique_ptr<TitleA> _window_title;

    /* COLUMNS */
    /* Two columns: City chart is on the left. Diversity and Happiness charts are on the right.*/

    /* COMMON TO ALL CHARTS */

    int _text_width_multiplier = 0.3;
    AxisFormat _axis_format_X{};
    AxisFormat _axis_format_Y{};

    // _used for Num Of Runs, City, Diversity, and Happiness chart titles
    Letter _chart_title_letter = Letter(30, 6, 0.3); 
    
    // space per chart in the x direction
    int _x_chart_space__px = _x_center__px - _side_borders__px - _col_inside_border__px; 

    // At the start of the axis, leave a space of cell size or point size times offset.
    // At the end of the axis, leave a space of cell size or point size times overrun.
    const int _x_offset_multiplier  = 1;
    const int _x_overrun_multiplier = 1;
    const int _y_offset_multiplier  = 1;
    const int _y_overrun_multiplier = 1;

    int _space_between_charts_y__px = 10;

    /* RUNS COUNTER */
    
    // Sits center, below window title
    int _runs_chart_top_y__px = _top_border__px + _window_title->sizeYPx();
    std::unique_ptr<GrRunsChart> _runs_chart;

    /* RIGHT COLUMN */

    // Right column holds the diversity chart and happiness chart
    int _chart_y_space__px = 
        _screen_height__px - //1200
        _top_border__px - //20
        _window_title->sizeYPx() - //42
        _chart_title_letter.getHeightIncLSpace() - // Runs chart //36
        _bottom_border__px - //20
        _space_between_charts_y__px; //10

    // Diversity and Happiness charts use the same dot size and copy of the same color key //TODO not the same dot size
    Letter _chart_key_letter{24, 12, 0.3};
    int _min_unit_size__px = 6;
    

    /* DIVERSITY CHART */

    // Diversity chart is the right column
    // Diversity chart sits below number of runs chart
    int _div_chart_top_y__px = _runs_chart_top_y__px + _chart_title_letter.getHeightIncLSpace();

    double _diversity_chart_y_axis_fraction = 0.3;

    int _max_number_of_neighbors;
    
    PlotSizer _div_sizer{
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _chart_key_letter,
        _min_unit_size__px,
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
        _space_between_charts_y__px;

    double _hap_chart_y_axis_fraction = 0.7;

    PlotSizer _hap_sizer{
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _chart_key_letter,
        _min_unit_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier,
        true
    };

    std::unique_ptr<GrHapChart> _happiness_chart;

    std::vector<int> determineMinMaxHouseCoords (
        std::unordered_map<const House*, Coordinate > coordPerHouse
    );


    /* CITY MAP CHART */

    // City map chart is in the left column and sits below number of runs chart
    int _city_map_chart_top_left_y_coord__px = 
        _runs_chart_top_y__px +
        _chart_title_letter.getHeightIncLSpace(); // Number of Runs chart// TODO get height of runs from the runs chart height
    
    int _city_y_space__px = 
        _screen_height__px -
        _top_border__px -
        _window_title->sizeYPx() -
        _chart_title_letter.getHeightIncLSpace() - // Number of Runs Chart height // TODO get from chart not from letter given to chart
        _bottom_border__px;

    // Each house is inside of a square cell. The cell 
    // will hold a house (represented by a colored square) and have
    // clear border around the house.
    // difficult to see, if smaller than _smallest_allowable_cell_size__px
    int _smallest_allowable_cell_size__px = 8; 
    int _cell_size;  // pixels for square cell
    int _house_size; // pixels for colored square house

    PlotSizer _city_plot_sizer{
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _chart_key_letter,
        _min_unit_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier,
        true
    };

    std::unique_ptr<GrCityChart>  _city_chart;



    int determineMaxNumberOfNeighbors (
        std::unordered_map<const House*,
        std::set<const House*>> neighbors
    );

    std::unique_ptr<TitleA> createWindowTitle (
        Letter letter,
        int topCenterX__px,
        int topCenterY__px,
        std::string title
    );

    std::unique_ptr<GrCityChart> createCityChart (
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

    std::unique_ptr<GrRunsChart> createRunsChart (int numOfRuns);

    int cityChartCalculatePxPerUnit(
        int minXCoord, 
        int maxXCoord, 
        int minYCoord, 
        int maxYCoord
    );
};

#endif