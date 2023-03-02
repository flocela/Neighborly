#include "GrRunsChart.h"

using namespace std;

GrRunsChart::GrRunsChart ( 
    int topLeftCornerXPx,
    int topLeftCornerYPx,
    int xSpaceLengthPx,
    int ySpaceLengthPx,
    Letter titleLetter,
    int numOfRuns
): _x_offset{topLeftCornerXPx},
   _y_offset{topLeftCornerYPx},
   _x_space_length__px{xSpaceLengthPx},
   _y_space_length__px{ySpaceLengthPx},
   _title_letter{titleLetter},
   _num_of_runs{numOfRuns}
{}

void GrRunsChart::print (int numOfRuns, Renderer* renderer) const
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