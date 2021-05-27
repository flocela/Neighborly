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
            const std::size_t grid_width, 
            const std::size_t grid_height
        );
        Printer_Graphic (const Printer_Graphic& obj) = default;
        Printer_Graphic (Printer_Graphic&& obj) noexcept = default;
        Printer_Graphic& operator= (const Printer_Graphic& obj) = default;
        Printer_Graphic& operator= (Printer_Graphic&& obj) noexcept = default;
        ~Printer_Graphic () = default;

        void printScreen ();

        void print(
            std::map<int, Resident*> residentPerHouse, 
            std::map<Coordinate, int> addressPerCoordinate,
            int run,
            int totalRuns,
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
        Renderer _renderer;
        std::thread poll_thread;
        void pollEvent();
        bool _keep_polling;
        std::map<Color, std::vector<int>> _rgba_per_color;
};

#endif