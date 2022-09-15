#ifndef GR_RUNS_CHART_H
#define GR_RUNS_CHART_H

#include "renderer.h"
#include <iostream>
#include "Letter.h"

// Graphic Run Counter Printer (prints the current run number).
class GrRunsChart
{
    public:
        GrRunsChart () = delete;
        GrRunsChart ( 
            int topLeftCornerXPx,
            int topLeftCornerYPx,
            int xSpaceLengthPx,
            int ySpaceLengthPx,
            Letter titleLetter,
            int widthMultiplier
        ):
            _x_offset{topLeftCornerXPx},
            _y_offset{topLeftCornerYPx},
            _x_space_length__px{xSpaceLengthPx},
            _y_space_length__px{ySpaceLengthPx},
            _title_letter{titleLetter},
            _width_multiplier{widthMultiplier}
        {}
        GrRunsChart (const GrRunsChart& obj) = default;
        GrRunsChart (GrRunsChart&& obj) noexcept = default;
        GrRunsChart& operator= (const GrRunsChart& obj) = default;
        GrRunsChart& operator= (GrRunsChart&& obj) noexcept = default;
        ~GrRunsChart () = default;

        void print (int numOfRuns, Renderer* renderer);
    
    private:
        int _x_offset = 0;
        int _y_offset = 0;
        int _x_space_length__px = 0;
        int _y_space_length__px = 0;
        Letter _title_letter;
        int _width_multiplier; // TODO use _widht_multiplier
        int _num_of_runs = 0;
};

#endif