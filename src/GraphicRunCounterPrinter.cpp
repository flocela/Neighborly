#include "GraphicRunCounterPrinter.h"

void GraphicRunCounterPrinter::print (int numOfRuns)
{   std::cout << "GraphicRun 4 " << std::endl;
    _renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        16
    );
    std::cout << "GraphicRun 10 " << _x_offset << std::endl;
    _renderer->renderText(
        _x_offset, 
        _y_offset,
        "Runs: " + std::to_string(numOfRuns) + " ",
        3);
}