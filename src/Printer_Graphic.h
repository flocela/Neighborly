#ifndef PRINTER_Graphic_H
#define PRINTER_Graphic_H

#include <memory>
#include <thread>
#include <unordered_set>
#include <vector>
#include "Color.h"
#include "House.h"
#include "GrCityChart.h"
#include "GrColorKey.h"
#include "GrDvstyChart.h"
#include "GrHapChart.h"
#include "GrRunsChart.h"
#include "Letter.h"
#include "PlotFormat.h"
#include "Printer.h"
#include "Renderer.h"
#include "RunMetrics.h"
#include "Title.h"
#include "Title_Basic.h"

//  Displays CityMap, Diversity Chart, and HappinessChart.
//  Uses a screen width and height of 2400px.
//  The left half of the screen holds the CityMap.
//  The right half of the screen holds the Diversity Chart above the HappinessChart.
class Printer_Graphic : public Printer
{   
public:
    Printer_Graphic (
        std::unique_ptr<Renderer> renderer,
        std::unordered_map<int, BaseColor> colors,
        std::unordered_map<const House*, Coordinate> coordinatesPerHouse,
        std::unordered_map<const House*, std::unordered_set<const House*>> neighborHousesPerHouse,
        std::string title,
        int numOfRuns
    );
    Printer_Graphic () = delete;
    Printer_Graphic (const Printer_Graphic& o) = default;
    Printer_Graphic (Printer_Graphic&& o) noexcept = default;
    Printer_Graphic& operator= (const Printer_Graphic& o) = default;
    Printer_Graphic& operator= (Printer_Graphic&& o) noexcept = default;
    ~Printer_Graphic () = default;
    // TODO should this be included in Printer interface
    void keepScreen();

    void print(
        const RunMetrics* runMetrics,
        int run
    ) const override;

private:

    // Renderer is mutable because the print() function calls the renderer's draw functions.
    // These functions are non-const, the renderer is changed.
    // However, calling print (which is const) doesn't change any other PrinterGraphic attributes.
    mutable std::unique_ptr<Renderer> _renderer;

    /* FOR WINDOW */
    int _screen_width__px  = 2400;
    int _screen_height__px = 1200;
    int _top_border__px = 10;
    int _bottom_border__px = 30;
    int _side_borders__px = 50; // both the left and right borders are this value
    int _col_inside_border__px = 50;
    int _x_center__px = _screen_width__px/2; // center of screen

    std::unordered_map<int, BaseColor> _colors;
    
    std::unordered_map<const House*, Coordinate> _coordinates_per_house = {};
    
    Letter _window_title_letter{44, 5, 0.35};
    std::unique_ptr<Title_Basic> _window_title;
    std::vector<uint8_t> _title_text_color = {255, 255, 255, 255};
    
    /* COLUMNS */
    /* Two columns: City chart is on the left. Diversity and Happiness charts are on the right.*/

    /* COMMON TO ALL OR MOST CHARTS */

    AxisFormat _axis_format_X{};
    AxisFormat _axis_format_Y{};
    Letter _chart_title_letter{30, 5, 0.35}; 
    Letter _chart_key_letter{24, 10, 0.35};
    int _min_unit_size__px = 6; // TODO write note of how this is used. Is it honored?

    // At the start of the axis, leave a space equal to cell size times offset multiplier.
    // At the end of the axis, leave a space equal to cell size times overrun multiplier.
    const int _x_offset_multiplier  = 1;
    const int _x_overrun_multiplier = 1;
    const int _y_offset_multiplier  = 1;
    const int _y_overrun_multiplier = 1;

    int _chart_space_x__px = _x_center__px - _side_borders__px - _col_inside_border__px;

    /* RUNS COUNTER */
    /* Sits below the window title, horizontally at center of window */

    int _num_of_runs;
    int _runs_chart_top_y__px;
    std::unique_ptr<GrRunsChart> _runs_chart;
    
    /* RIGHT COLUMN */
    /* Right column holds the diversity chart above the happiness chart */
    

    /* DIVERSITY CHART */
    /* Diversity chart is the right column. Diversity chart sits below number of runs chart*/
    
    std::string _div_chart_title =  "Average Number of Disparate Neighbors per Group, per Run";

    double _div_chart_y_axis_fraction = 0.3;

    // provides some vertical space between diversity and happiness charts.
    double _space_below_div_chart_y_axis_fraction = 0.01; 

    int _max_number_of_neighbors; //TODO we need to set this and honor it.

    std::unique_ptr<GrDvstyChart> _div_chart;
    
    /* HAPPINESS CHART */
    /* Happiness chart is the right column. Happiness chart sits below diversity chart*/
    
    std::string _hap_chart_title =  "Average Resident Happiness per Group, per Run";

    std::unique_ptr<GrHapChart> _happiness_chart;

    /* LEFT COLUMN */
    /* Left column holds the city chart */

    std::string _city_chart_title = "City Map";

    // Determines the smallest and largest x and y values on the grid, per the house coordinates.
    // Returns a vector {smallest x value, largest x value, smallest y value, largest y value}
    std::vector<int> determineMinMaxHouseCoords (
        std::unordered_map<const House*, Coordinate > coordPerHouse
    );

    std::unique_ptr<GrCityChart>  _city_chart;

    // Finds the house with the largest number of adjacent houses from the unordered_map given.
    // Returns the number of adjacent houses.
    int determineMaxNumberOfAdjHouses (
        std::unordered_map<const House*,std::unordered_set<const House*>> neighbors
    );

    std::unique_ptr<GrCityChart> createCityChart (
        int minXCoord, 
        int maxXCoord, 
        int minYCoord, 
        int maxYCoord,
        int topLeftYPx,
        int availSpaceYPx);

    std::unique_ptr<GrDvstyChart> createDvstyChart(
        std::unordered_map<const House*, std::unordered_set<const House*>> neighbors,
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