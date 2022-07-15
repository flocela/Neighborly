#ifndef PRINTER_Graphic_H
#define PRINTER_Graphic_H

#include "GrCityPrinter.h"
#include "Printer.h"
#include "renderer.h"
#include <thread>
#include <memory>
#include "House.h"
#include <vector>
#include "Color.h"
#include "GraphicRunCounterPrinter.h"
#include "GrDiversityPrinter.h"
#include "Letter.h"

class Printer_Graphic : public Printer
{   
    public:
        Printer_Graphic() = delete;
        Printer_Graphic (
            const int screen_width,
            const int screen_height
        );
        Printer_Graphic (const Printer_Graphic& obj) = default;
        Printer_Graphic (Printer_Graphic&& obj) noexcept = default;
        Printer_Graphic& operator= (const Printer_Graphic& obj) = default;
        Printer_Graphic& operator= (Printer_Graphic&& obj) noexcept = default;
        ~Printer_Graphic () = default;

        void initCityMap (City* cityPtr); // make private
        void setColors (std::map<int, std::pair<Color, Color>> colors); // make private
        void initRunCounter (int numOfRuns); // make private
        void init (City* cityPtr, int numOfRuns);
        int maxNumOfHousesX (int screenWidth__px);
        int maxNumOfHousesY (int screenHeight__px);

        void print(
            std::map<House*, Resident*> residentPerHouse,
            int run,
            std::string title
        ) override;

        void keepScreen();
    
    private:
        std::unique_ptr<GrCityPrinter>       _city_printer;
        std::unique_ptr<GraphicRunCounterPrinter> _run_counter_printer;
        std::unique_ptr<GrDiversityPrinter>  _diversity_printer;

        std::map<Coordinate, House*> _coord_to_house_map = {};
        std::set<Color> colors = {
            Color::red,
            Color::blue,
            Color::green
        };
        std::unique_ptr<Renderer> _renderer;
        std::map<int, std::pair<Color, Color>> _colors;
        int _num_of_types_of_residents = 2;

        // all X axes have the same length
        int allowableLengthXAxes (int screenWidth__px);

        // sum of all Y axes (City Map, Diversity Chart, Happiness Chart)
        int allowableLengthForYAxes (int screenWidth__px);

        // The sum of the Y axes for map chart, diversity chart, and happiness chart
        int calcSumOfYSpacesPx ();
        int calcXSpacePx();

        int calcLeftXCoordPx(); // same for all three charts.
        int calcCityMapChartTopLeftYCoordPx ();
        int calcDivChartTopLeftYCoordPx ();

        // FOR WINDOW //
        int _screen_width__px;
        int _screen_height__px;

        int _top_border__px = 10;
        int _bottom_border__px = 10;
        int _left_border__px = 10;
        int _right_border__px = 10;

        Letter _window_title = Letter(24, 2);
        int _window_title_w__px = 100; // main title width
        int _window_title_y__px = _top_border__px; // top left corner of text
        int _window_title_x__px;// top left corner of text
        
        Letter _resident_keys = Letter (12, 2); // shows resident next to its colored square

        // COMMON TO ALL CHARTS //
        AxisFormat _axis_format_X{};
        AxisFormat _axis_format_Y{};
        Letter _chart_title_letter = Letter(30, 2); // used for Num Of Runs, City Map, Diversity...

        int _charts_top_left_x_coord__px; // x-coordinate for top left corner of all charts is the same
        int _x_space_length__px; // Same in all charts so charts line up.
        int _sum_y_space_lengths__px; // all three chart's y direction spaces added up.
        const int x_axis_offset__px = 2;
        const int x_axis_overrun__px = 2;
        const int y_axis_offset__px = 2;
        const int y_axis_overrrun__px = 2;

        // MAP OF CIY HOUSES CHART//
        double _city_map_y_axis_fraction = 0.5;
        int _map_writable_vert_length__px; // TODO - probably not useful
        int _map_y_axis_length__px;
        int _city_map_chart_top_left_y_coord__px;

        // Each house is inside of a square cell. The cell 
        // will hold a house (represented by a colored square) and have
        // clear border around the house.
        int _smallest_allowable_cell_size__px = 4; // can't see house, if smaller
        int _cell_size;  // pixels for square cell
        int _house_size; // pixels for colored square house
        int _city_tick_spacing_x; // tick spacing on x axis
        int _city_tick_spacing_y; // tick spacing on y axis
        int _city_label_spacing_x; // label spacing on x axis
        int _city_label_spacing_y; // label spacing on y axis
        
        // House coordinates from the city, not in pixels. // TODO maybe move this to COMMON TO ALL CHARTS
        int _min_x_coord = INT32_MAX; // top left corner of grid 
		int _min_y_coord = INT32_MAX; // top left corner of grid
		int _max_x_coord = INT32_MIN; // bottom right corner of grid
		int _max_y_coord = INT32_MIN; // bottom right corner of grid
        
        //DIVERSITY CHART
        double _diversity_chart_y_axis_fraction = 0.25;
        int _div_chart_y_top_left_y_coord__px;


        //HAPPINESS CHART
        int _hap_chart_y_axis_length__px;

        // RUNS COUNTER CHART//
        int _num_runs_title_w__px = 50; // run title widths
        int _curr_run = 0;
        int _num_of_runs;

        // x and y offsets for title displaying number of runs so far. // TODO what is this for?
        const int _x_num_of_runs_offset = 80;
        const int _y_num_of_runs_offset = 80;

        // Moves the city's non-changing information into class attributes
        // (which by the way will also not be changing). For example since
        // the City's houses' coordinates will not change, 
        // initialize _coord_to_house_map. 
        // Since, the city's most west, east, north, and south coordinates
        // will not change, set _min_x_coord and the like.
        void determineMinMaxHouseCoords (City* cityPtr);

        // determines _cell_size and _house_size.
        void setCityMapInfo ();

        // initialize _graphic_city_printer with base information
        // like where to put grid (graphOrigin), x and y axis offsets,
        // cell_size, rgba for residents' colors and the like. Basically 
        // set up the graph where the residents will be plotted.
        void setCityPrinter ();

        void initDiversityPrinter();

        void initAxesValues ();



};

#endif