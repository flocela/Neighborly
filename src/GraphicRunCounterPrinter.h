#ifndef GRAPHIC_RUN_COUNTER_PRINTER_H
#define GRAPHIC_RUN_COUNTER_PRINTER_H

#include "renderer.h"
#include <iostream>

class GraphicRunCounterPrinter
{
    public:
        GraphicRunCounterPrinter () = delete;
        GraphicRunCounterPrinter ( 
            Renderer* renderer,
            int xOffset, 
            int yOffset,
            int maxNumOfRuns
        ):
            _renderer{renderer},
            _x_offset{xOffset},
            _y_offset{yOffset},
            _max_num_of_runs{maxNumOfRuns}
        {
            std::cout << "Graphic run .h 22: " << _x_offset << std::endl;
        }
        GraphicRunCounterPrinter (const GraphicRunCounterPrinter& obj) = default;
        GraphicRunCounterPrinter (GraphicRunCounterPrinter&& obj) noexcept = default;
        GraphicRunCounterPrinter& operator= (const GraphicRunCounterPrinter& obj) = default;
        GraphicRunCounterPrinter& operator= (GraphicRunCounterPrinter&& obj) noexcept = default;
        ~GraphicRunCounterPrinter () = default;

        void print (int numOfRuns);
    
    private:
        Renderer* _renderer;
        int _x_offset = 0;
        int _y_offset = 0;
        int _max_num_of_runs = 0;
        int _num_of_runs = 0;
};

#endif