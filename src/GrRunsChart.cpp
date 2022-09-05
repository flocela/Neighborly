#include "GrRunsChart.h"

void GrRunsChart::print (int numOfRuns)
{   
    _renderer->setTextFormats(
        {100, 100, 100, 100}, 
        {0xAA, 0xFF, 0xFF, 0xFF}, 
        _title_letter.letterHeight()
    );
    _renderer->renderText(
        _x_offset + (_x_space_length__px/2), 
        _y_offset,
        "Runs: " + std::to_string(numOfRuns) + " ",
        1);
}