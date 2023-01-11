#include "GrRunsChart.h"

using namespace std;
void GrRunsChart::print (int numOfRuns, Renderer* renderer)
{   
    renderer->renderText(
        _x_offset + (_x_space_length__px/2), 
        _y_offset,
        "Runs: " + to_string(numOfRuns) + " ",
        _title_letter.letterHeight(),
        _title_letter.widthMultiplier(),
        _text_color,
        _text_background_color,
        1);
}

int GrRunsChart::sizeXPx ()
{
    // number of letters is eight corresponding to "Runs: 999. assuming there is less than 1,000 runs."
    return (int)(9 * _title_letter.widthMultiplier() * _title_letter.letterHeight());
}

int GrRunsChart::sizeYPx ()
{
    return _title_letter.getHeightIncLSpace();
}