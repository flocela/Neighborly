#ifndef PRINTER_Graphic_H
#define PRINTER_Graphic_H

#include "Printer.h"
#include "renderer.h"
#include <thread>

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
            std::map<int, Resident*> residentPerHouse,
            int run,
            int totRuns,
            std::string title
        ) override;
        void printResidents (
            std::map<int, Resident*> housePerResident,
            std::map<int, Coordinate> coordinatePerHouse,
            int run,
            int totRuns,
            std::string title
        ) override;

        void keepScreen();
    
    private:
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
        std::map<Coordinate, int> _housePerCoordinate = {};

        Renderer _renderer;
        std::thread poll_thread;
        void pollEvent();
        bool _keep_polling;
        std::map<Color, std::vector<int>> _rgba_per_color;
        std::map<Color, std::vector<Coordinate>> createVectorsForEachColor (
            std::map<int, Resident*> residentPerHouse
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