#ifndef GR_RUNS_CHART_H
#define GR_RUNS_CHART_H

#include <iostream>

#include "Color.h"
#include "Letter.h"
#include "Renderer.h"

// Used to render the current run number.
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
    );
    GrRunsChart () = delete;
    GrRunsChart (const GrRunsChart& obj) = default;
    GrRunsChart (GrRunsChart&& obj) noexcept = default;
    GrRunsChart& operator= (const GrRunsChart& obj) = default;
    GrRunsChart& operator= (GrRunsChart&& obj) noexcept = default;
    ~GrRunsChart () noexcept = default;

    void print (int numOfRuns, Renderer* renderer) const;
    int sizeXPx () const;
    int sizeYPx () const;

private:

    int _x_offset = 0;
    int _y_offset = 0;

    // allowed space in the x-direction
    int _x_space_length__px = 0;

    // allowed space in the y-direction
    int _y_space_length__px = 0;
    Letter _title_letter;
    int _num_of_runs;
    std::vector<uint8_t> _text_color = _the_color_rgba[Color::gray100];
    std::vector<uint8_t> _text_background_color =  _the_color_rgba[Color::gray900];

};

#endif