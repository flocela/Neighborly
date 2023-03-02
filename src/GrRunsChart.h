#ifndef GR_RUNS_CHART_H
#define GR_RUNS_CHART_H

#include "Renderer.h"
#include <iostream>
#include "Letter.h"
#include "SDL.h"

// Graphic Run Counter Printer (prints the current run number).
class GrRunsChart
{

public:

    GrRunsChart ( 
        int topLeftCornerXPx,
        int topLeftCornerYPx,
        int xSpaceLengthPx,
        int ySpaceLengthPx,
        Letter titleLetter,
        int numOfRuns
    ):
        _x_offset{topLeftCornerXPx},
        _y_offset{topLeftCornerYPx},
        _x_space_length__px{xSpaceLengthPx},
        _y_space_length__px{ySpaceLengthPx},
        _title_letter{titleLetter},
        _num_of_runs{numOfRuns}
    {}
    GrRunsChart () = delete;
    GrRunsChart (const GrRunsChart& obj) = default;
    GrRunsChart (GrRunsChart&& obj) noexcept = default;
    GrRunsChart& operator= (const GrRunsChart& obj) = default;
    GrRunsChart& operator= (GrRunsChart&& obj) noexcept = default;
    ~GrRunsChart () = default;

    void print (int numOfRuns, Renderer* renderer) const;
    int sizeXPx ();
    int sizeYPx ();

private:

    int _x_offset = 0;
    int _y_offset = 0;
    int _x_space_length__px = 0;
    int _y_space_length__px = 0;
    Letter _title_letter;
    int _num_of_runs;
    SDL_Color _text_color = {100, 100, 100, 100};
    SDL_Color _text_background_color = {0xAA, 0xFF, 0xFF, 0xFF};

};

#endif