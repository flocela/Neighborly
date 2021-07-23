#include "GraphicRunCounterPrinter.h"

void GraphicRunCounterPrinter::print (int numOfRuns)
{   
    _renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        16
    );
    _renderer->renderText(
        _x_offset, 
        _y_offset,
        "Runs: " + std::to_string(numOfRuns) + " ",
        3);
}