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
#include "GrColorKey.h"
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
        std::unordered_map<int, BaseColor> colors,
        std::unordered_map<const House*, Coordinate > coordPerHouse,
        std::unordered_map<const House*, std::set<const House*>> neighborHouses,
        std::string title,
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
    int _top_border__px = 30;
    int _bottom_border__px = 50;
    int _side_borders__px = 50; // both the left and right borders are this value
    int _col_inside_border__px = 50;
    int _x_center__px = _screen_width__px/2; // center of screen

    std::unordered_map<int, BaseColor> _colors;
    
    std::unordered_map<const House*, Coordinate> _coordinates_per_house = {};

    std::unique_ptr<Renderer> _renderer = std::make_unique<Renderer>(
        _screen_width__px,
        _screen_height__px
    );
    
    Letter _window_title_letter{50, 10, 0.3};
    std::unique_ptr<TitleA> _window_title;
    
    /* COLUMNS */
    /* Two columns: City chart is on the left. Diversity and Happiness charts are on the right.*/

    /* COMMON TO ALL OR MOST CHARTS */

    AxisFormat _axis_format_X{};
    AxisFormat _axis_format_Y{};
    Letter _chart_title_letter = Letter(30, 10, 0.3); 
    Letter _chart_key_letter{24, 12, 0.3};
    int _min_unit_size__px = 6; // TODO write note of how this is used. Is it honored?

    // At the start of the axis, leave a space equal to cell size times offset.
    // At the end of the axis, leave a space equal to cell size times overrun.
    const int _x_offset_multiplier  = 1;
    const int _x_overrun_multiplier = 1;
    const int _y_offset_multiplier  = 1;
    const int _y_overrun_multiplier = 1;

    int _chart_space_x__px = _x_center__px - _side_borders__px - _col_inside_border__px;

    /* RUNS COUNTER */
    /* Sits horizontally at center of window, below window title */

    int _num_of_runs;
    int _runs_chart_top_y__px;
    std::unique_ptr<GrRunsChart> _runs_chart;
    
    /* RIGHT COLUMN */
    /* Right column holds the diversity chart and happiness chart */
    
    PlotSizer _right_col_sizer{
        _axis_format_X,
        _axis_format_Y,
        _chart_title_letter,
        _chart_key_letter,
        _min_unit_size__px,
        _x_offset_multiplier,
        _x_overrun_multiplier,
        true
    };

    /* DIVERSITY CHART */
    /* Diversity chart is the right column. Diversity chart sits below number of runs chart*/
    
    double _div_chart_y_axis_fraction = 0.3;

    int _max_number_of_neighbors; //TODO we need to set this and honor it.

    std::unique_ptr<GrDvstyChart> _div_chart;
    
    /* HAPPINESS CHART */
    /* Happiness chart is the right column. Happiness chart sits below diversity chart*/
    
    std::unique_ptr<GrHapChart> _happiness_chart;

    /* LEFT COLUMN */
    /* Left column holds the city chart */

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

    std::vector<int> determineMinMaxHouseCoords (
        std::unordered_map<const House*, Coordinate > coordPerHouse
    );

    std::unique_ptr<GrCityChart>  _city_chart;

    int determineMaxNumberOfNeighbors (
        std::unordered_map<const House*,
        std::set<const House*>> neighbors
    );

    std::unique_ptr<GrCityChart> createCityChart (
        int minXCoord, 
        int maxXCoord, 
        int minYCoord, 
        int maxYCoord,
        int topLeftYPx,
        int availSpaceYPx);

    std::unique_ptr<GrDvstyChart> createDvstyChart(
        std::unordered_map<const House*, std::set<const House*>> neighbors,
        int maxNumOfNeighbors,
        int maxNumOfRuns,
        int topLeftYPx,
        int availSpaceYPx
    );

    std::unique_ptr<GrHapChart> createHapChart (
        int numberOfRuns,
        int topLeftYPx,
        int availSpaceYPx
    );
};

#endif