#include "GrRunsChart.h"

void GrRunsChart::print (int numOfRuns, Renderer* renderer)
{   
    renderer->renderText(
        _x_offset + (_x_space_length__px/2), 
        _y_offset,
        "Runs: " + std::to_string(numOfRuns) + " ",
        _title_letter.letterHeight(),
        _title_letter.widthMultiplier(),
        _text_color,
        _text_background_color,
        1);
}

int GrRunsChart::sizeXPx ()
{
    // number of letters assumes number of runs is less than 10,000
    // number of letters is eight corresponding to "Runs: 999".
    return (int)(8 * _title_letter.widthMultiplier() * _title_letter.letterHeight());
}

int GrRunsChart::sizeYPx ()
{
    return _title_letter.getHeightIncLSpace();
}