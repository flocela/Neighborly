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
#include "GrRunCPrinter.h"
#include "GrDiversityPrinter.h"
#include "GrHappinessPrinter.h"
#include "GrColorKeyPrinter.h"
#include "Letter.h"
#include "GrDvstyPrinter.h"
#include "GrHapPrinter.h"

//  Displays CityMap, Diversity Chart, and HappinessChart.
//  Uses a screen width and height of 2400px.
class Printer_Graphic : public Printer
{   
    public:
        Printer_Graphic () = default;
        Printer_Graphic (const Printer_Graphic& obj) = default;
        Printer_Graphic (Printer_Graphic&& obj) noexcept = default;
        Printer_Graphic& operator= (const Printer_Graphic& obj) = default;
        Printer_Graphic& operator= (Printer_Graphic&& obj) noexcept = default;
        ~Printer_Graphic () = default;

        void initCityMap (City* cityPtr); // make private
        void setColors (std::unordered_map<int, Color> colors); // make private
        void initRunCounter (int numOfRuns); // make private
        void initColorKeyForCityMap();
        void initColorKeyForDivAndHapCharts();
        void init (City* cityPtr, int numOfRuns, std::string title);
        int maxNumOfHousesX (int screenWidth__px);
        int maxNumOfHousesY (int screenHeight__px);

        void print(
            std::unordered_map<House*, Resident*> residentPerHouse,
            int run
        ) override;

        void keepScreen();
    
    private:
        std::unique_ptr<GrCityPrinter>      _city_printer;
        std::unique_ptr<GrRunCPrinter>      _run_counter_printer;
        std::unique_ptr<GrDiversityPrinter> _diversity_printer;
        std::unique_ptr<GrHapPrinter>     _happiness_printer;
        std::unique_ptr<GrDvstyPrinter>     _dvsty_printer;
        std::unique_ptr<GrColorKeyPrinter>  _color_key_for_map_printer;
        std::unique_ptr<GrColorKeyPrinter>  _color_key_for_hap_and_div_printer;

        City* _city;

        std::map<Coordinate, House*> _coord_to_house_map = {};
        std::unique_ptr<Renderer> _renderer;
        std::unordered_map<int, Color> _colors;
        int _num_of_types_of_residents = 2;

        // * FOR WINDOW * //
        int _screen_width__px  = 2400;
        int _screen_height__px = 1200;

        int _top_border__px    = 10;
        int _bottom_border__px = 10;
        int _side_border__px   = 20; // left and right border is same.
        int _inside_border__px = 10; // left column's left border, and right column's right border

        Letter _window_title = Letter(40, 2);
        std::string _window_title_string = "Neighbors";
        int _window_title_x__px;// top left corner of text
        int _window_title_y__px = _top_border__px; // top left corner of text
        
        Letter _resident_keys = Letter (12, 2); // shows resident next to its colored square

        // * COMMON TO ALL CHARTS * //
        AxisFormat _axis_format_X{};
        AxisFormat _axis_format_Y{};
        Letter _chart_title_letter = Letter(30, 6); // used for Num Of Runs, City Map, Diversity...
        int _x_space_length__px; // total x space minus the side borders
        int _x_space__px; // space per chart
        int _x_center__px; // center of screen

        // At the start of the axis, leave a space of cell size or point size times offset.
        // At the end of the axis, leave a space of cell size or point size times overrun.
        const int _x_offset_multiplier  = 2;
        const int _x_overrun_multiplier = 2;
        const int _y_offset_multiplier   = 2;
        const int _y_overrun_multiplier  = 2;

        int _space_between_charts__px = 35; // vertical space

        // * RUNS COUNTER *// 
        // Sits center, below window title
        int _run_counter_top_y__px;
        int _curr_run = 0;
        int _num_of_runs;

        // * MAP OF CIY HOUSES CHART, RIGHT COLUMN * //
        int _city_y_space__px;
        int _city_map_chart_top_left_y_coord__px;

        //  COLOR KEY FOR MAP OF CITY
        int _color_key_for_city_map_top_y__px;

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
        
        //   House coordinates from the city, not in pixels.
        int _min_x_coord = INT32_MAX; // top left corner of grid 
		int _min_y_coord = INT32_MAX; // top left corner of grid
		int _max_x_coord = INT32_MIN; // bottom right corner of grid
		int _max_y_coord = INT32_MIN; // bottom right corner of grid

        // * DIVERSITY CHART, HAPPINESS CHART LEFT COLUMN* //
        int _chart_y_space__px;
        int _color_key_for_div_and_hap_top_y__px;
        Letter _color_key_letter{24, 4};
        
        //DIVERSITY CHART
        double _diversity_chart_y_axis_fraction = 0.3;
        int _div_chart_top_y__px;
        int _dot_size__px = 4;

        // HAPPINESS CHART
        double _hap_chart_y_axis_fraction = 0.7;
        int _hap_chart_top_y__px;

        

        // COLOR KEY FOR DIVERSITY AND HAPPINESS CHARTS
        Letter _color_key_letter_for_map{24, 4}; // TODO is this used. Should be replace dby _color_key_letter

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

        void initHappinessPrinter();

        void printWindowTitle();

        void initWindowTitle(std::string title);
        
        // these are distances.
        void initWindowLengths();

        int cityPrinterCalculatePxPerUnit();



};

#endif