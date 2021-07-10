#ifndef PRINTER_Graphic_H
#define PRINTER_Graphic_H

#include "GraphicCityPrinter.h"
#include "Printer.h"
#include "renderer.h"
#include <thread>
#include <memory>
#include "House.h"

class Printer_Graphic : public Printer
{   
    public:
        Printer_Graphic() = delete;
        Printer_Graphic (
            const std::size_t screen_width,
            const std::size_t screen_height,
            City* cityPtr
        );
        Printer_Graphic (const Printer_Graphic& obj) = default;
        Printer_Graphic (Printer_Graphic&& obj) noexcept = default;
        Printer_Graphic& operator= (const Printer_Graphic& obj) = default;
        Printer_Graphic& operator= (Printer_Graphic&& obj) noexcept = default;
        ~Printer_Graphic () = default;

        void print(
            std::map<House*, Resident*> residentPerHouse,
            int run,
            int totRuns,
            std::string title
        ) override;

        void keepScreen();
    
    private:
        std::unique_ptr<GraphicCityPrinter> _graphic_city_printer;
        std::size_t _screen_width;
        std::size_t _screen_height;
        // Each house is inside of a grid square. The grid square 
        // will hold a house (represented by a colored square) and a
        // clear border around the house.
        int _grid_size;
        int _house_size;
        int _min_x_coord = INT32_MAX;
		int _min_y_coord = INT32_MAX;
		int _max_x_coord = INT32_MIN;
		int _max_y_coord = INT32_MIN;

        // chart title is vertically offset from the origin by _title_offset
		// from the x-axis by x-title-offset
		const int _title_offset = 10;

		// x-axis is vertically offset from origin by x-axis-offset
		const int _x_axis_offset = 10;

        // y-axis is vertically offset from origin by y-axis-offset
		const int _y_axis_offset = 10;

		// x-axis overruns its data by x_axis_overrun
		const int _x_axis_overrun = 0;

        // y-axis overruns its data by y_axis_overrun
		const int _y_axis_overrun = 0;

        // titlesAtTopOffset and titlesLeftOffset is room given for titles at top
        // and left of the graph.
        // fontSize is for x and y axes.
        const int _titles_at_left_offset = 240;
        const int _titles_at_top_offset = 80;
        const int _axis_font_size = 20;
        
        std::map<Coordinate, House*> _coord_to_house_map = {};

        Renderer _renderer;
        std::map<Color, std::vector<int>> _rgba_per_color;
        std::map<Color, std::vector<Coordinate>> createVectorsForEachColor (
            std::map<House*, Resident*> houseToResidentMap
        );
        // Initializes information from the city that will not change. Each 
        // address's coordinate will stay the same. So the _housePerCoordinate map
        // is initialized. The city's most west, east, north, and south coordinates
        // will not change. So the min, max, x, and y coordinates 
        // from the city are initialized (i.e. _min_x_coord).
        void initCityCoordinateInfo (City* cityPtr);
        // Initializes information about the graph based on the city 
        // and screen sizes.
        void initGridAndHouseSize ();

};

#endif